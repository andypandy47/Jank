#pragma once

#ifdef JANK_PLATFORM_WINDOWS
	#ifdef JANK_BUILD_DLL
		#define JANK_API __declspec(dllexport)
	#else
		#define JANK_API __declspec(dllimport)
	#endif
#else
	#error Jank only supports Windows!
#endif

#define BIT(x) (1 << x)