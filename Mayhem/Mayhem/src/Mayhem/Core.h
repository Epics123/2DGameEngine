#pragma once

#ifdef MH_PLATFORM_WINDOWS
	#ifdef MH_BUILD_DLL
		#define MAYHEM_API __declspec(dllexport)
	#else 
		#define MAYHEM_API __declspec(dllimport)
	#endif // MH_BUILD_DLL
#else
	#error Mayhem only supports Windows!
#endif // MH_PLATFORM_WINDOWS

