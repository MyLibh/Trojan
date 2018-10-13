#pragma once

#ifndef __SCREENCAPTURER_HPP_INCLUDED__
#define __SCREENCAPTURER_HPP_INCLUDED__

class ScreenCapturer final
{
private:
	class DirectXImpl;
	class WinCodec
	{
	public:
		WinCodec();
		~WinCodec();

	public:
		IWICImagingFactory    *m_pFactory;
		IWICBitmapEncoder     *m_pEncoder;
		IWICBitmapFrameEncode *m_pFrame;
		IWICStream            *m_pStream;
	};

public:
	ScreenCapturer();
	~ScreenCapturer();

	inline       LPBYTE get_data()            noexcept { return (m_pData); }
	inline const LPBYTE get_data()      const noexcept { return (m_pData); }
	inline const size_t get_data_size() const noexcept { return (m_data_size); }

	bool capture();
	bool save2png(const std::filesystem::path &path);

private:
	DirectXImpl *m_pImpl;
	size_t       m_data_size;
	LPBYTE       m_pData;
};

#endif /* __SCREENCAPTURER_HPP_INCLUDED__ */