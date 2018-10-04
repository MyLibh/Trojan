#include "..\pch.h"

#include "WebCamCapturer.hpp"

VideoDevice::VideoDevice() :
	m_friendly_name(),
	m_filter_name(),
	m_pFilter(nullptr)
{ }

std::string VideoDevice::get_friendly_name() const
{
	return m_friendly_name;
}
