#include <d3d9.h>
#include <Wincodec.h> 

#pragma comment(lib, "d3d9.lib")

template<typename T>
VOID SafeRelease(T **pPtr)
{
	if (*pPtr)
	{
		(*pPtr)->Release();

		*pPtr = nullptr;
	}
}

LPBYTE CaptureScreen()
{
	IDirect3D9 *pD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D9)
	{
		return nullptr;
	}

	D3DDISPLAYMODE mode = { 0 };
	if(pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode) != D3D_OK)
	{
		return nullptr;
	}

	D3DPRESENT_PARAMETERS parameters = { 0 };
	parameters.Windowed         = TRUE;
	parameters.BackBufferCount  = 1;
	parameters.BackBufferHeight = mode.Height;
	parameters.BackBufferWidth  = mode.Width;
	parameters.SwapEffect       = D3DSWAPEFFECT_DISCARD;

	IDirect3DDevice9 *pDevice = nullptr;
	if (pD3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, nullptr, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &pDevice) != D3D_OK)
	{
		return nullptr;
	}


	IDirect3DSurface9 *pSurface = nullptr;
	if (pDevice->CreateOffscreenPlainSurface(mode.Width, mode.Height, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &pSurface, nullptr) != D3D_OK)
	{
		return nullptr;
	}
	
	D3DLOCKED_RECT rc = { 0 };
	if (pSurface->LockRect(&rc, nullptr, 0) != D3D_OK)
	{
		return nullptr;
	}

	UINT pitch = rc.Pitch;
	if (pSurface->UnlockRect() != D3D_OK)
	{
		return nullptr;
	}

	LPBYTE shot = new BYTE[pitch * mode.Height];
	pDevice->GetFrontBufferData(0, pSurface);
	pSurface->LockRect(&rc, nullptr, 0);
	CopyMemory(shot, rc.pBits, rc.Pitch * mode.Height);
	pSurface->UnlockRect();

cleanup:

	SafeRelease(&pSurface);
	SafeRelease(&pDevice);
	SafeRelease(&pD3D9);

	return shot;
}