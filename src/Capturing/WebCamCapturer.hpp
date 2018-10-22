#pragma once

#ifndef __WEBCAMCAPTURER_HPP_INCLUDED__
#define __WEBCAMCAPTURER_HPP_INCLUDED__

class VideoDevice
{
public:
	VideoDevice();

	std::string get_friendly_name() const;

private:
	std::string	  m_friendly_name;
	std::wstring  m_filter_name;
	IBaseFilter  *m_pFilter;

	friend class VideoCapture;
};

#endif /* __WEBCAMCAPTURER_HPP_INCLUDED__ */