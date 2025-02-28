# test options, dont do anything for now
option(USE_VULKAN "Use Vulkan renderer" ON)
option(USE_OPENGL "Use OpenGL renderer" OFF)
option(ENABLE_LOGGING "Enable logging" ON)
option(ENABLE_PROFILING "Enable profiling" OFF)

# For some reason assimp don't want to run with gtests
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
