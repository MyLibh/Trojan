#pragma once

#ifndef __SCREENCAPTURER_HPP_INCLUDED__
#define __SCREENCAPTURER_HPP_INCLUDED__

class ScreenCapturer : private boost::noncopyable
{
private:
	class DirectXImpl;
	class WinCodec
	{
	public:
		WinCodec() noexcept;
		~WinCodec();

	public:
		IWICImagingFactory    *m_pFactory; //-V122
		IWICBitmapEncoder     *m_pEncoder; //-V122
		IWICBitmapFrameEncode *m_pFrame; //-V122
		IWICStream            *m_pStream; //-V122
	};

public:
	ScreenCapturer() noexcept;
	~ScreenCapturer();

	inline       BYTE*  release_data()         { return &m_pData[0]; }
	inline const size_t get_data_size() const noexcept { return (m_data_size); }

	bool capture();
	bool save2png(const std::filesystem::path &path);

private:
	std::unique_ptr<DirectXImpl> m_pImpl;
	size_t                       m_data_size; //-V122
	std::shared_ptr<BYTE[]>      m_pData; //-V122
};

#endif /* __SCREENCAPTURER_HPP_INCLUDED__ */