#pragma once
#include<memory>

#ifdef YE_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
	#ifdef YE_BUILD_DLL
		#define YSJEN_API __declspec(dllexport)
	#else
		#define YSJEN_API __declspec(dllimport)
	#endif
#else
	#define YSJEN_API
#endif
#else
	#error YSJEN only support Windows
#endif // YE_PLATFORM_WINDOWS

#ifdef YE_DEBUG
	#define YE_ENABLE_ASSERTS
#endif // YE_DEBUG


#ifdef YE_ENABLE_ASSERTS
	#define YE_ASSERT(x, ...) { if(!(x)) { YE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define YE_CORE_ASSERT(x, ...) { if(!(x)) { YE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define YE_ASSERT(x, ...)
	#define YE_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1<<x)

#define YE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace YSJEN {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
