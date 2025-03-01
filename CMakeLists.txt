cmake_minimum_required (VERSION 3.30)
project ("FancyRenderer" VERSION 0.0.1)
find_package(PkgConfig REQUIRED)

include(cmake/options.cmake)
include(cmake/platform.cmake)
include(cmake/compiler.cmake)
include(cmake/deps.cmake)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
message(STATUS "Root directory: ${ROOT_DIR}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(src)

add_executable(${PROJECT_NAME} ${ALL_SRC_FILES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Vulkan::Vulkan
    glfw
    assimp::assimp
    glm::glm
    VulkanMemoryAllocator
    Engine
    Common
)

if(APPLE)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation"
    )
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE src/engine/core/include
                                                   src/common/include)
