#pragma once

#ifdef MH_PLATFORM_WINDOWS
#if MH_DYNAMIC_LINK
	#ifdef MH_BUILD_DLL
		#define MAYHEM_API __declspec(dllexport)
	#else 
		#define MAYHEM_API __declspec(dllimport)
	#endif // MH_BUILD_DLL
#else
	#define MAYHEM_API
#endif
#else
	#error Mayhem only supports Windows!
#endif // MH_PLATFORM_WINDOWS

#ifdef MH_DEBUG
	#define MH_ENABLE_ASSERTS
#endif // MH_DEBUG


#ifdef MH_ENABLE_ASSERTS
	#define MH_ASSERT(x, ...) { if(!(x)) { MH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MH_CORE_ASSERT(x, ...) { if(!(x)) { MH_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MH_ASSERT(x, ...)
	#define MH_CORE_ASSERT(x, ...)
#endif // MH_ENABLE_ASSERS

#define MH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

//#define BIT(x) = (1 << x)