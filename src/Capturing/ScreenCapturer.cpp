// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "ScreenCapturer.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Service\Log.hpp"

namespace detail
{
	template<typename T, typename = void>
	struct has_Release_func : std::false_type
	{ };

	template<typename T>
	struct has_Release_func<T, std::void_t<decltype(std::declval<T>().Release())>> : std::true_type
	{ };

	template<typename T>
	constexpr bool has_Release_func_v = has_Release_func<T>::value;

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	template<typename T>
	void SafeRelease(T *ptr) noexcept
	{
		if constexpr (has_Release_func_v<T>)
		{
			if (ptr)
			{
				ptr->Release();

				ptr = nullptr;
			}
		}

	}

}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ScreenCapturer::DirectXImpl::init() noexcept
{
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION); //-V2001
	if (!m_pD3D9)
		return false;

	if (m_pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_mode) != D3D_OK)
		return false;

	D3DPRESENT_PARAMETERS parameters{ };
	parameters.Windowed         = true;
	parameters.BackBufferCount  = 1;
	parameters.BackBufferHeight = m_mode.Height;
	parameters.BackBufferWidth  = m_mode.Width;
	parameters.SwapEffect       = D3DSWAPEFFECT_DISCARD;

	if (m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, nullptr, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &m_pDevice) != D3D_OK)
		return false;

	if (m_pDevice->CreateOffscreenPlainSurface(m_mode.Width, m_mode.Height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &m_pSurface, nullptr) != D3D_OK)
		return false;

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenCapturer::DirectXImpl::release() noexcept
{
	detail::SafeRelease(m_pSurface);
	detail::SafeRelease(m_pDevice);
	detail::SafeRelease(m_pD3D9);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
inline bool ScreenCapturer::WinCodec::init() noexcept
{
	return (CoInitializeEx(nullptr, COINIT_MULTITHREADED) == S_OK);	
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenCapturer::WinCodec::release() noexcept
{
	detail::SafeRelease(m_pStream);
	detail::SafeRelease(m_pFrame);
	detail::SafeRelease(m_pEncoder);
	detail::SafeRelease(m_pFactory);

	CoUninitialize();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void ScreenCapturer::init() 
{
	m_dxImpl = ScreenCapturer::DirectXImpl::create_with_deleter<DirectXImpl>();
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ScreenCapturer::capture()
{
	UINT           pitch{ };
	D3DLOCKED_RECT rc{ };
	auto ptr{ m_dxImpl->m_pSurface };
	if (ptr->LockRect(&rc, nullptr, 0) != D3D_OK)
		return false;

	pitch = rc.Pitch;
	if (ptr->UnlockRect() != D3D_OK)
		return false;

	m_data_size = gsl::narrow_cast<std::size_t>(pitch) * gsl::narrow_cast<std::size_t>(m_dxImpl->m_mode.Height);

	m_data = std::make_unique<BYTE[]>(m_data_size);

	if (m_dxImpl->m_pDevice->GetFrontBufferData(0, m_dxImpl->m_pSurface) != D3D_OK)
		return false;

	if (ptr->LockRect(&rc, nullptr, 0) != D3D_OK)
		return false;

#pragma warning(suppress : 6387) 
	// warning C6387: 'rc.pBits' could be '0':  this does not adhere to the specification for the function 'memcpy'.
	std::memcpy(m_data.get(), rc.pBits, gsl::narrow_cast<std::size_t>(rc.Pitch) * gsl::narrow_cast<std::size_t>(m_dxImpl->m_mode.Height));

	if (m_dxImpl->m_pSurface->UnlockRect() != D3D_OK)
		return false;

	return true;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool ScreenCapturer::save2png(const std::filesystem::path &path)
{
	std::shared_ptr<WinCodec> pWC     { ScreenCapturer::WinCodec::create_with_deleter<WinCodec>() };
	if (CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWC->m_pFactory)) != S_OK) //-V2001
		return false;

	if (pWC->m_pFactory->CreateStream(&pWC->m_pStream) != S_OK)
		return false;

	if (pWC->m_pStream->InitializeFromFilename(path.generic_wstring().c_str(), GENERIC_WRITE) != S_OK)
		return false;

	auto pEncoder{ pWC->m_pEncoder };
	if (pWC->m_pFactory->CreateEncoder(GUID_ContainerFormatJpeg, nullptr, &pEncoder) != S_OK)
		return false;
	
	if (pEncoder->Initialize(pWC->m_pStream, WICBitmapEncoderNoCache) != S_OK)
		return false;

	auto pFrame{ pWC->m_pFrame };
	if (pEncoder->CreateNewFrame(&pFrame, nullptr) != S_OK)
		return false;

	if (pFrame->Initialize(nullptr) != S_OK)
		return false;

	const D3DDISPLAYMODE mode{ m_dxImpl->m_mode };
	if (pFrame->SetSize(mode.Width, mode.Height) != S_OK)
		return false;

	if (GUID format{ GUID_WICPixelFormat32bppPBGRA }; pFrame->SetPixelFormat(&format) != S_OK)
		return false;

	if (pFrame->WritePixels(mode.Height, gsl::narrow_cast<UINT>(m_data_size) / gsl::narrow_cast<UINT>(mode.Height), gsl::narrow_cast<UINT>(m_data_size), m_data.get()) != S_OK)
		return false;

	if (pFrame->Commit() != S_OK)
		return false;

	if (pEncoder->Commit() != S_OK)
		return false;

	return true;
}

