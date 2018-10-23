// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "ScreenCapturer.hpp"
#include "..\Service\Debugger.hpp"

namespace detail
{
	template<typename T>
	void SafeRelease(T *ptr)
	{
		if (ptr)
		{
			ptr->Release();

			ptr = nullptr;
		}
	}
}

ScreenCapturer::WinCodec::WinCodec() :
	m_pFactory(nullptr),
	m_pEncoder(nullptr),
	m_pFrame(nullptr),
	m_pStream(nullptr)
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
}

ScreenCapturer::WinCodec::~WinCodec()
{
	detail::SafeRelease(m_pStream);
	detail::SafeRelease(m_pFrame);
	detail::SafeRelease(m_pEncoder);
	detail::SafeRelease(m_pFactory);

	CoUninitialize();
}


class ScreenCapturer::DirectXImpl
{
public:
	~DirectXImpl();

	BOOL init();

public:
	IDirect3D9        *m_pD3D9; //-V122
	IDirect3DDevice9  *m_pDevice; //-V122
	IDirect3DSurface9 *m_pSurface; //-V122
	D3DDISPLAYMODE     m_mode;
};

ScreenCapturer::DirectXImpl::~DirectXImpl()
{
	detail::SafeRelease(m_pSurface);
	detail::SafeRelease(m_pDevice);
	detail::SafeRelease(m_pD3D9);
}

BOOL ScreenCapturer::DirectXImpl::init()
{
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_pD3D9)
		return false;

	if (m_pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_mode) != D3D_OK)
		return false;

	D3DPRESENT_PARAMETERS parameters = { 0 };
	parameters.Windowed = TRUE;
	parameters.BackBufferCount = 1;
	parameters.BackBufferHeight = m_mode.Height;
	parameters.BackBufferWidth = m_mode.Width;
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if (m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, nullptr, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &m_pDevice) != D3D_OK)
		return FALSE;

	if (m_pDevice->CreateOffscreenPlainSurface(m_mode.Width, m_mode.Height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &m_pSurface, nullptr) != D3D_OK)
		return FALSE;

	return TRUE;
}


ScreenCapturer::ScreenCapturer() :
	m_pImpl(new ScreenCapturer::DirectXImpl),
	m_data_size(0ull),
	m_pData(nullptr)
{
	if (!m_pImpl->init())
		$ERROR("Smth went wrong during DirectX initialization\n");
}

ScreenCapturer::~ScreenCapturer()
{
	// delete m_pImpl;
}

bool ScreenCapturer::capture()
{
	UINT pitch        = 0;
	D3DLOCKED_RECT rc = { 0 };
	if (m_pImpl->m_pSurface->LockRect(&rc, nullptr, 0) != D3D_OK)
		goto error;

	pitch = rc.Pitch;
	if (m_pImpl->m_pSurface->UnlockRect() != D3D_OK)
		goto error;

	m_data_size = static_cast<size_t>(pitch * m_pImpl->m_mode.Height);
	if (m_pData)
		m_pData = nullptr;

	m_pData = std::make_unique<BYTE[]>(m_data_size);

	if (m_pImpl->m_pDevice->GetFrontBufferData(0, m_pImpl->m_pSurface) != D3D_OK)
		goto error;

	if (m_pImpl->m_pSurface->LockRect(&rc, nullptr, 0) != D3D_OK)
		goto error;

	std::memcpy(&m_pData, rc.pBits, static_cast<size_t>(rc.Pitch) * static_cast<size_t>(m_pImpl->m_mode.Height));

	if (m_pImpl->m_pSurface->UnlockRect() != D3D_OK)
		goto error;

	return true;

error:
	m_data_size = 0;
	m_pData     = nullptr;

	return false;
}

bool ScreenCapturer::save2png(const std::filesystem::path &path)
{
	std::unique_ptr<WinCodec> pWC{ new WinCodec };
	GUID                      format{ GUID_WICPixelFormat32bppPBGRA };
	HRESULT                   hr{ S_OK };

#define CHECK_HRESULT(ret_val) { hr = ret_val; if(hr != S_OK) { $ERROR("Error(0x%08X) on line(%d)\n", hr, __LINE__) goto end; } }
	CHECK_HRESULT(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWC->m_pFactory)))
	CHECK_HRESULT(pWC->m_pFactory->CreateStream(&pWC->m_pStream))
	CHECK_HRESULT(pWC->m_pStream->InitializeFromFilename(path.generic_wstring().c_str(), GENERIC_WRITE))
	CHECK_HRESULT(pWC->m_pFactory->CreateEncoder(GUID_ContainerFormatJpeg, nullptr, &pWC->m_pEncoder))
	CHECK_HRESULT(pWC->m_pEncoder->Initialize(pWC->m_pStream, WICBitmapEncoderNoCache))
	CHECK_HRESULT(pWC->m_pEncoder->CreateNewFrame(&pWC->m_pFrame, nullptr))
	CHECK_HRESULT(pWC->m_pFrame->Initialize(nullptr))
	CHECK_HRESULT(pWC->m_pFrame->SetSize(m_pImpl->m_mode.Width, m_pImpl->m_mode.Height))
	CHECK_HRESULT(pWC->m_pFrame->SetPixelFormat(&format))
	CHECK_HRESULT(pWC->m_pFrame->WritePixels(m_pImpl->m_mode.Height, static_cast<UINT>(m_data_size) / m_pImpl->m_mode.Height, static_cast<UINT>(m_data_size), &m_pData[0]))
	CHECK_HRESULT(pWC->m_pFrame->Commit())
	CHECK_HRESULT(pWC->m_pEncoder->Commit())
#undef CHECK_HRESULT

end:
	return (hr == S_OK);
}

