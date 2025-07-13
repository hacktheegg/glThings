cmake_minimum_required(VERSION 3.10)
project(glThings)

# Create GLAD library directly
add_library(glad STATIC
    "${PROJECT_SOURCE_DIR}/dep/glad/src/glad.c"
    "${PROJECT_SOURCE_DIR}/dep/glad/include/glad/glad.h"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set include directory for GLAD
target_include_directories(glad PUBLIC
    "${PROJECT_SOURCE_DIR}/dep/glad/include"
)

# Add GLFW subdirectory
add_subdirectory("${PROJECT_SOURCE_DIR}/dep/glfw")

# Add GLM subdirectory
add_subdirectory("${PROJECT_SOURCE_DIR}/dep/glm")

# Define source and header files
set(SOURCES
    "${PROJECT_SOURCE_DIR}/src/main.cpp"
)

set(HEADERS
    "${PROJECT_SOURCE_DIR}/src/renderer.hpp"
    "${PROJECT_SOURCE_DIR}/src/shader_s.hpp"
)

# Check if this is the top-level project
if(PROJECT_IS_TOP_LEVEL)
    # Build as executable
    add_executable(glThings ${SOURCES} ${HEADERS})

    # Link all dependencies
    target_link_libraries(glThings
        PRIVATE glad
        PRIVATE glfw
        PRIVATE glm::glm
    )

    # Set include directories
    target_include_directories(glThings PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/dep/glad/include
        ${PROJECT_SOURCE_DIR}/dep/glfw/include
        ${PROJECT_SOURCE_DIR}/dep/glm
    )
else()
    # Build as library
    add_library(glThings STATIC
        ${SOURCES}
        ${HEADERS}
    )

    # Link all dependencies
    target_link_libraries(glThings
        PRIVATE glad
        PRIVATE glfw
        PRIVATE glm::glm
    )

    # Set include directories
    target_include_directories(glThings PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/dep/glad/include
        ${PROJECT_SOURCE_DIR}/dep/glfw/include
        ${PROJECT_SOURCE_DIR}/dep/glm
    )
endif()

