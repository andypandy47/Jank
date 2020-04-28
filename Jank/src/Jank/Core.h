#pragma once

#include <memory>

#ifdef JANK_PLATFORM_WINDOWS
#if JANK_DYNAMIC_LINK
	#ifdef JANK_BUILD_DLL
		#define JANK_API __declspec(dllexport)
	#else
		#define JANK_API __declspec(dllimport)
	#endif
#else
	#define JANK_API
#endif
#else
	#error Jank only supports Windows!
#endif

#ifdef JANK_DEBUG
	#define JANK_ENABLE_ASSERTS
#endif

#ifdef JANK_ENABLE_ASSERTS
	#define JANK_ASSERT(x, ...) { if(!(x)) {JANK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JANK_CORE_ASSERT(x, ...) { if(!(x)) {JANK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JANK_ASSERT(x, ...)
	#define JANK_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Jank
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}