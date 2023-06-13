#pragma once

#ifdef CB_PLATFORM_WINDOWS
	#ifdef CB_BUILD_DLL
		#define CHICKEN_API __declspec(dllexport)
	#else
		#define CHICKEN_API __declspec(dllimport)
	#endif
#else
	#error ChickenBroth only supports Windows!
#endif // CB_PLATFORM_WINDOWS

#define BIT(x) (1 << x)