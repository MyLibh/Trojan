#pragma once

#ifndef __PCH_HPP_INCLUDED__
#define __PCH_HPP_INCLUDED__

// C RunTime Header Files
#include <stdlib.h> 
#include <stdio.h>  
#include <io.h>

// C++ RunTime Header Files
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include <algorithm>
#include <deque>
#include <thread>
#include <tuple>
#include <variant>
#include <bitset>
#include <filesystem>

// Windows Header Files
#include <sdkddkver.h>
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN 
#endif /* WIN32_LEAN_AND_MEAN */
#include <Windows.h>
#include <shellapi.h>
#include <tchar.h> 
#include <d3d9.h>
#include <dshow.h>
#include <wincodec.h>
 
// Additional Libraries Header Files
#include <boost\asio.hpp>
#include <boost\bind.hpp>

// My Header Files
#include "Constants.hpp"

#endif /* __PCH_H_INCLUDED__ */

