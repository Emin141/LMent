cmake_minimum_required(VERSION 3.10)
project(LMent)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set C standard for C files
set(CMAKE_C_STANDARD 99) 

# Find SFML
find_package(SFML 2.5 REQUIRED graphics window system)

# Setup include directories
include_directories(include third_party/include)

# Recursively find all .cpp files in the src directories
file(GLOB_RECURSE SOURCES "src/*.cpp" "third_party/src/*.c")

# Setup for Debug Build
add_executable(LMent_Debug ${SOURCES})
target_compile_definitions(LMent_Debug PRIVATE DEBUG_BUILD SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)
target_compile_options(LMent_Debug PRIVATE -O0 -g -Werror -Wall)
target_link_libraries(LMent_Debug sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(LMent_Debug GL)  # OpenGL library on Linux
target_link_libraries(LMent_Debug dl)  # Dynamic linking library

# Setup for Release Build
add_executable(LMent ${SOURCES})
target_compile_definitions(LMent PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO)
target_compile_options(LMent PRIVATE -O2 -Werror -Wall)
target_link_libraries(LMent sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
target_link_libraries(LMent GL)  # OpenGL library on Linux
target_link_libraries(LMent dl)  # Dynamic linking library
