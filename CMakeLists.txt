cmake_minimum_required(VERSION 3.16...3.28 FATAL_ERROR)

project(glThings VERSION 1.0.0 LANGUAGES CXX HOMEPPE_URL "")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLTHINGS_BUILD_EXAMPLES "Build the glThings example programs" OFF)
option(GLTHINGS_BUILD_TESTS "Build the glThings test programs" OFF)
option(GLTHINGS_BUILD_DOCS "Build the glThings documentation" ON)
option(GLTHINGS_INSTALL "Generate installation target" ON)

include(GNUInstallDirs)
include(CMakeDependentOption)

set_property(TARGET glThings PROPERTY CXX_STANDARD 11)
set_property(TARGET glThings PROPERTY CXX_STANDARD_REQUIRED TRUE)

# Platform-specific options
cmake_dependent_option(GLTHINGS_USE_WIN32 "Build support for Win32" ON "WIN32" OFF)
cmake_dependent_option(GLTHINGS_USE_LINUX "Build support for Linux" ON "UNIX" OFF)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")

if(GLTHINGS_USE_WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/windows")
endif()
if(GLTHINGS_USE_LINUX)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/linux")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${CMAKE_BINARY_DIR}/include/glad/include")

add_subdirectory("${CMAKE_BINARY_DIR}/include/glfw")
add_subdirectory("${CMAKE_BINARY_DIR}/include/glm")

configure_file("${CMAKE_BINARY_DIR}/src/shaders/shader.vert" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
configure_file("${CMAKE_BINARY_DIR}/src/shaders/shader.frag" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

add_executable(glThings "${CMAKE_BINARY_DIR}/src/main.cpp" "${CMAKE_BINARY_DIR}/include/glad/src/glad.c")
target_link_libraries(glThings glfw)

# Installation configuration
if(GLTHINGS_INSTALL)
    include(CMakePackageConfigHelpers)

    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/glThingsConfig.cmake.in
        ${CMAKE_BINARY_DIR}/src/glThingsConfig.cmake
        INSTALL_DESTINATION "${GLTHINGS_CONFIG_PATH}"
        NO_CHECK_REQUIRED_COMPONENTS_MACRO
    )

    write_basic_package_version_file(
        ${CMAKE_BINARY_DIR}/src/glThingsConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
    )

    # Install headers
    install(DIRECTORY include/glad/include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # Install config files
    install(
        FILES "${CMAKE_BINARY_DIR}/src/glThingsConfig.cmake"
              "${CMAKE_BINARY_DIR}/src/glThingsConfigVersion.cmake"
        DESTINATION "${GLTHINGS_CONFIG_PATH}"
    )

    # Install export target
    install(EXPORT glThingsTargets
            FILE glThingsTargets.cmake
            DESTINATION "${GLTHINGS_CONFIG_PATH}")

    # Create uninstall target
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in
        cmake_uninstall.cmake
        IMMEDIATE @ONLY
    )

    add_custom_target(uninstall
                      "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")
endif()
