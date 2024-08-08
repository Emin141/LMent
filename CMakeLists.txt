cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Minesweeper VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(Minesweeper src/main.cpp)

# Find and link SFML (assuming SFML is installed in the default locations)
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(Minesweeper sfml-system sfml-window sfml-graphics)

# Include directories
target_include_directories(Minesweeper PRIVATE include)

