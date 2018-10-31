#pragma once

#ifndef __SCREENCAPTURER_HPP_INCLUDED__
#define __SCREENCAPTURER_HPP_INCLUDED__

#include "..\Service\NeedPostInit.hpp"

class ScreenCapturer : public NeedPostInit
{
private:
	class DirectXImpl : public NeedPostInit
	{
	public:
		bool init() noexcept;

		void release() noexcept;

	public:
		IDirect3D9        *m_pD3D9; //-V122
		IDirect3DDevice9  *m_pDevice; //-V122
		IDirect3DSurface9 *m_pSurface; //-V122
		D3DDISPLAYMODE     m_mode;
	};

	class WinCodec : public NeedPostInit
	{
	public:
		bool init() noexcept;

		void release() noexcept;

	public:
		IWICImagingFactory    *m_pFactory; //-V122
		IWICBitmapEncoder     *m_pEncoder; //-V122
		IWICBitmapFrameEncode *m_pFrame;   //-V122
		IWICStream            *m_pStream;  //-V122
	};

public:
	void init();
	
	inline       std::shared_ptr<BYTE[]> get_data()            noexcept{ return (m_data); }
	inline const std::size_t             get_data_size() const noexcept { return (m_data_size); }

	bool capture();
	bool save2png(const std::filesystem::path &path);

private:
	std::shared_ptr<DirectXImpl> m_dxImpl;
	std::size_t                  m_data_size; //-V122
	std::shared_ptr<BYTE[]>      m_data; 
};

#endif /* __SCREENCAPTURER_HPP_INCLUDED__ */