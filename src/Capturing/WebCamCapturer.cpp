// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

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
