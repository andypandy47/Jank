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

#ifdef JANK_ENABLE_ASSERTS
	#define JANK_ASSERT(x, ...) { if(!(x)) {HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JANK_CORE_ASSERT(x, ...) { if(!(x)) {HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JANK_ASSERT(x, ...)
	#define JANK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)