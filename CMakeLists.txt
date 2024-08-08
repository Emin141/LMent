cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

# Find SFML
find_package(SFML 2.5 REQUIRED graphics window system)

# Set the default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Recursively find all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable target
add_executable(Minesweeper ${SOURCES})

# Link SFML libraries
target_link_libraries(Minesweeper sfml-graphics sfml-window sfml-system)

# Add compile options for Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Minesweeper PRIVATE -g -O0)
endif()
