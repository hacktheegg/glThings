cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)

project(glThings VERSION 1.0.0 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLTHINGS_BUILD_EXAMPLES "Build the glThings example programs" OFF)
option(GLTHINGS_BUILD_TESTS "Build the glThings test programs" OFF)
option(GLTHINGS_BUILD_DOCS "Build the glThings documentation" ON)
option(GLTHINGS_INSTALL "Generate installation target" ON)

include(GNUInstallDirs)
include(CMakeDependentOption)

# Platform-specific options
cmake_dependent_option(GLTHINGS_USE_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(GLTHINGS_USE_LINUX "Build support for Linux" ON "UNIX" OFF)

# Change from executable to static library
add_library(glThings STATIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/src/glad.c"
)

# Set properties on the library
set_property(TARGET glThings PROPERTY CXX_STANDARD 11)
set_property(TARGET glThings PROPERTY CXX_STANDARD_REQUIRED TRUE)

# Replace the include_directories() calls with target_include_directories()
target_include_directories(glThings PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glfw/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/glm"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Add subdirectories
add_subdirectory(include/glfw)
add_subdirectory(include/glm)

# Link libraries
target_link_libraries(glThings glfw)

