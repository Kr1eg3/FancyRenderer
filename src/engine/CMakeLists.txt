cmake_minimum_required (VERSION 3.31)
project("Engine")

file(GLOB_RECURSE SRC_NESTED
  ${PROJECT_SOURCE_DIR}/*.cpp )
set(ALL_SRC_FILES ${SRC_NESTED})

add_library(${PROJECT_NAME} STATIC ${ALL_SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC core/include)

target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan glfw glm::glm Common)
