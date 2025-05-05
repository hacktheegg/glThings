cmake_minimum_required(VERSION 3.10)
project(glThings)



set(SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")
set(HEADERS "${PROJECT_SOURCE_DIR}/src/physSolver.hpp")
set(HEADERS "${PROJECT_SOURCE_DIR}/src/renderer.hpp")
set(HEADERS "${PROJECT_SOURCE_DIR}/src/shader_s.hpp")



add_library(glThings STATIC ${SOURCES})
target_include_directories(glThings PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)



set_target_sources(glThings PRIVATE ${SOURCES} ${HEADERS})
