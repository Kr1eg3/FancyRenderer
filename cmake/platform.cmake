if(WIN32)
    add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_WIN32_KHR")
elseif(APPLE)
    add_definitions(-DVK_USE_PLATFORM_MACOS_MVK)
    add_definitions(-DVK_USE_PLATFORM_METAL_EXT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_MACOS_MVK -DVK_USE_PLATFORM_METAL_EXT")
endif()
