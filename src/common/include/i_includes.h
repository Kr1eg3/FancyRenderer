
#pragma once

#ifdef _WIN32
#ifndef VK_USE_PLATFORM_WIN32_KHR
    #define VK_USE_PLATFORM_WIN32_KHR
#endif
#elif defined(__APPLE__)
#ifndef VK_USE_PLATFORM_MACOS_MVK
    #define VK_USE_PLATFORM_MACOS_MVK
#endif
#ifndef VK_USE_PLATFORM_METAL_EXT
    #define VK_USE_PLATFORM_METAL_EXT
#endif
#endif

#include <vulkan/vulkan.h>
#include <vulkan/vk_enum_string_helper.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#ifdef _WIN32
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#elif defined(__APPLE__)
    #define GLFW_EXPOSE_NATIVE_COCOA
    #include <GLFW/glfw3native.h>
#endif

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/hash.hpp>

#include <iostream>
#include <memory>
#include <algorithm>

#ifdef _WIN32
    typedef VkWin32SurfaceCreateInfoKHR PlatformSurfaceCreateInfo;
#elif defined(__APPLE__)
    typedef VkMacOSSurfaceCreateInfoMVK PlatformSurfaceCreateInfo;
#endif

#ifdef _WIN32
    #define PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define PLATFORM_MACOS
#endif

#ifdef PLATFORM_WINDOWS
    #define PLATFORM_SURFACE_EXTENSION VK_KHR_WIN32_SURFACE_EXTENSION_NAME
#elif defined(PLATFORM_MACOS)
    #define PLATFORM_SURFACE_EXTENSION VK_MVK_MACOS_SURFACE_EXTENSION_NAME
#endif

inline bool IsPlatformWindows() {
#ifdef PLATFORM_WINDOWS
    return true;
#else
    return false;
#endif
}

inline bool IsPlatformMacOS() {
#ifdef PLATFORM_MACOS
    return true;
#else
    return false;
#endif
}
