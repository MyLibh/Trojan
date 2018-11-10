#pragma once

#ifndef __PCH_HPP_INCLUDED__
#define __PCH_HPP_INCLUDED__

// Preprocessor
#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING	// Hide warnings from boost

#ifdef _DEBUG
	#define _ITERATOR_DEBUG_LEVEL	2
#else /* ifdef NDEBUG */
	#define _ITERATOR_DEBUG_LEVEL	0
#endif /* ifdef _DEBUG */

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
#include <memory>
#include <execution>
#include <string>
#include <type_traits>

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

#ifdef min
	#undef min
#endif /* min */

#ifdef max
#undef max
#endif /* max */
 
// Additional Libraries Header Files
#pragma region boost
	#pragma warning(push)
	#pragma warning(disable : 6001 6031 6255 6258 6326 6330 6387 6388 26110 26135 26400 26401 26402 26409 26415 26418 26426 26429 26430 26432 26433 26434 26436 26438 26439 26440 26443 26444 26446 26447 26451 26455 26456 26460 26461 26462 26465 26466 26471 26472 26473 26474 26475 26476 26477 26481 26482 26485 26486 26487 26489 26490 26491 26492 26493 26494 26495 26496 26497 26498 28251)
		#include <boost\asio.hpp> 
		#include <boost\core\noncopyable.hpp>
		#include <boost\format.hpp>

		#include <boost\log\trivial.hpp>
		#include <boost\log\expressions.hpp>
		#include <boost\log\sources\logger.hpp>
		#include <boost\log\utility\setup\file.hpp>
		#include <boost\log\utility\setup\console.hpp>
		#include <boost\log\utility\setup\common_attributes.hpp>
		#include <boost\log\support\date_time.hpp>
	#pragma warning(pop)
#pragma endregion

#pragma region gsl
	#pragma warning(push)
	#pragma warning(disable : 26440 26487)
		#include <gsl\gsl>
	#pragma warning(pop)
#pragma endregion

// Turn off sime warnings
#pragma warning(disable : 26485)
// warning C26485: No array to pointer decay (bounds.3).

#endif /* __PCH_H_INCLUDED__ */

