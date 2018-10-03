#pragma once

#ifndef __SCREENCAPTURER_HPP_INCLUDED__
#define __SCREENCAPTURER_HPP_INCLUDED__

struct IDirect3D9;
struct IDirect3DDevice9;
struct IDirect3DSurface9;

	struct DirectXParametrs
	{
		IDirect3D9        *m_pD3D9;
		IDirect3DDevice9  *m_pDevice;
		IDirect3DSurface9 *m_pSurface;
		D3DDISPLAYMODE     m_mode;

		DirectXParametrs();
		~DirectXParametrs();

		BOOL init();
	};

	template<typename T>
	VOID SafeRelease(T **pPtr)
	{
		if (*pPtr)
		{
			(*pPtr)->Release();

			*pPtr = nullptr;
		}
	}

	LPBYTE CaptureScreen(DirectXParametrs *pDXParams);

#endif /* __SCREENCAPTURER_HPP_INCLUDED__ */