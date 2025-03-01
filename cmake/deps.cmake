include(FetchContent)

Set(FETCHCONTENT_QUIET FALSE) # Turn this on for GIT_PROGRESS in FetchContent_Declare

# Vulkan
find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Found Vulkan!")
endif()
if (APPLE)
    include_directories(
        /usr/local/include
        ${Vulkan_INCLUDE_DIRS}
    )

    link_directories(
        /usr/local/lib
    )
endif()

file(GLOB SRC_FILES
       ${PROJECT_SOURCE_DIR}/*.cpp)
set(ALL_SRC_FILES ${SRC_FILES})

set(DEPS
    vma
    glfw
    assimp
    glm
)

set(DEP_VERSIONS # Actual tag for FetchContent_Declare
    "3.2.1"
    "3.4"
    "5.4.1"
    "1.0.1"
)

set(DEP_TAGS
    "v3.2.1"
    "3.4"
    "v5.4.1"
    "1.0.1"
)

set(DEP_GITS
    https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator.git   # VMA
    https://github.com/glfw/glfw.git                                        # glfw
    https://github.com/assimp/assimp.git                                    # assimp
    https://github.com/g-truc/glm.git                                       # glm
)

foreach(DEP DEP_GIT DEP_VERSION DEP_TAG IN ZIP_LISTS DEPS DEP_GITS DEP_VERSIONS DEP_TAGS)
   message(STATUS "Start work with: ${DEP}")

   if(NOT ${DEP}_VERSION)
      set(${DEP}_VERSION ${DEP_VERSION})
   endif()
   message(STATUS "${DEP} version is: ${${DEP}_VERSION}")

   find_package(${DEP} ${${DEP}_VERSION} QUIET)
   if(${DEP}_FOUND)
      message(STATUS "Found ${DEP}!")
   else()
      message(STATUS "${DEP} ${${DEP}_VERSION} not found! Try to build it from sources")
      message(STATUS "Fetch content of ${DEP}: weblink: ${DEP_GIT}; tag: ${DEP_TAG}")

      FetchContent_Declare(
         ${DEP}
         GIT_REPOSITORY  ${DEP_GIT}
         GIT_TAG         ${DEP_TAG}
         GIT_PROGRESS    FALSE
      )

      FetchContent_MakeAvailable(${DEP})

      message(STATUS "Successfully fetched and built ${DEP} ${${DEP}_VERSION}")
   endif()
endforeach()
