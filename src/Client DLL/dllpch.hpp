#pragma once

#ifndef __DLLPCH_HPP_INCLUDED__
#define __DLLPCH_HPP_INCLUDED__

// C++ RunTime Header Files
#include <string>
#include <iostream>

// Windows Header Files
#include <sdkddkver.h>
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif /* WIN32_LEAN_AND_MEAN */
#include <Windows.h>
#include <tchar.h>

// Additional Libraries Header Files
#include <boost\asio.hpp>

#endif /* __DLLPCH_HPP_INCLUDED__ */