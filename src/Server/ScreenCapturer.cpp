#include "..\pch.h"

#include "ScreenCapturer.hpp"

DirectXParametrs::DirectXParametrs() :
	m_pD3D9(nullptr),
	m_pDevice(nullptr),
	m_pSurface(nullptr),
	m_mode({ 0 })
{ }

DirectXParametrs::~DirectXParametrs()
{
	SafeRelease(&m_pSurface);
	SafeRelease(&m_pDevice);
	SafeRelease(&m_pD3D9);
}

BOOL DirectXParametrs::init()
{
	m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_pD3D9)
		return FALSE;

	if (m_pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_mode) != D3D_OK)
		return FALSE;
	
	D3DPRESENT_PARAMETERS parameters = { 0 };
	parameters.Windowed         = TRUE;
	parameters.BackBufferCount  = 1;
	parameters.BackBufferHeight = m_mode.Height;
	parameters.BackBufferWidth  = m_mode.Width;
	parameters.SwapEffect       = D3DSWAPEFFECT_DISCARD;

	if (m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, nullptr, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &m_pDevice) != D3D_OK)
		return FALSE;
	
	if (m_pDevice->CreateOffscreenPlainSurface(m_mode.Width, m_mode.Height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &m_pSurface, nullptr) != D3D_OK)
		return FALSE;
	
	return TRUE;
}

LPBYTE CaptureScreen(DirectXParametrs *pDXParams)
{
	D3DLOCKED_RECT rc = { 0 };
	if (pDXParams->m_pSurface->LockRect(&rc, nullptr, 0) != D3D_OK)
		return nullptr;

	UINT pitch = rc.Pitch;
	if (pDXParams->m_pSurface->UnlockRect() != D3D_OK)
		return nullptr;

	LPBYTE shot = new BYTE[pitch * pDXParams->m_mode.Height]; // TODO: bad_alloc check
	if (pDXParams->m_pDevice->GetFrontBufferData(0, pDXParams->m_pSurface) != D3D_OK)
		goto error;

	if (pDXParams->m_pSurface->LockRect(&rc, nullptr, 0) != D3D_OK)
		goto error;

	CopyMemory(shot, rc.pBits, rc.Pitch * pDXParams->m_mode.Height);

	if (pDXParams->m_pSurface->UnlockRect() != D3D_OK)
		goto error;

	return shot;
	
error:
	delete[] shot;

	return nullptr;
}