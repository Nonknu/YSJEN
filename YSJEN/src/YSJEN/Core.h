#pragma once


#ifdef YE_PLATFORM_WINDOWS
	#ifdef YE_BULID_DLL
		#define YSJEN_API __declspec(dllexport)	
	#else
		#define YSJEN_API __declspec(dllimport)		
	#endif // 
#else
	#error YSJEN only support Windows
#endif // YE_PLATFORM_WINDOWS
