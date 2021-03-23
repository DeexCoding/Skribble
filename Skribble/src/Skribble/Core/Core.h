#pragma once

#include <memory>

#define SKRIBBLE_DISABLE 0
#define SKRIBBLE_ENABLE 1

//Platforms

#ifdef _WIN64
	#ifndef SKRIBBLE_WINDOWS
		#define SKRIBBLE_WINDOWS
	#endif 
#elif defined(_WIN32)
	#error "32bit is not supported!"
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>

	#if TARGET_IPHONE_SIMULATOR == SKRIBBLE_ENABLE
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == SKRIBBLE_ENABLE
	#error "IOS is not supported"
	#elif TARGET_OS_MAC == SKRIBBLE_ENABLE
		#ifndef SKRIBBLE_MAC
			#define SKRIBBLE_MAC
		#endif
		#error "Mac is not supported!"
	#endif
#elif defiend (__andorid__)
	#ifndef SKRIBBLE_ANDROID
		#define SKRIBBLE_ANDROID
	#endif 
	#error "Linux is not supported!"
#elif defined (__linux__)
	#ifndef SKRIBBLE_LINUX
		#define SKRIBBLE_LINUX
	#endif 
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif

//

//Debug

#ifdef SKRIBBLE_DEBUG
#if defined(SKRIBBLE_WINDOWS)
#define SKRIBBLE_DEBUGBREAK() __debugbreak()
#elif defined(SKRIBBLE_LINUX)
#include <signal.h>
#define SKRIBBLE_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define SKRIBBLE_ENABLE_ASSERTS
#else
#define SKRIBBLE_DEBUGBREAK()
#endif

#ifdef SKRIBBLE_ENABLE_ASSERTS
#define SKRIBBLE_ASSERT(x, ...) { if(!(x)) { SKRIBBLE_ERROR("Assertion failed : {0}", __VA_ARGS__); SKRIBBLE_DEBUGBREAK(); } }
#define SKRIBBLE_CORE_ASSERT(x, ...) { if(!(x)) { SKRIBBLE_CORE_ERROR("Assertion failed : {0}", __VA_ARGS__); SKRIBBLE_DEBUGBREAK(); } }
#else
#define SKRIBBLE_ASSERT(x, ...)
#define SKRIBBLE_CORE_ASSERT(x, ...)
#endif

//

#define BSR(x) (1 << x)
#define BSL(x) (1 >> x)

#define BIND_EVENTFUNCTION(x) std::bind(&x, this, std::placeholders::_1)

namespace Skribble
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}