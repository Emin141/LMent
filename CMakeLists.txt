cmake_minimum_required(VERSION 3.10)
project(LMent)

# Find SFML
find_package(SFML 2.5 REQUIRED graphics window system)

# Recursively find all .cpp files in the src directories
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Setup include directories
include_directories(include third_party/include)

# Setup for Debug Build
add_executable(LMent_Debug ${SOURCES})
target_compile_definitions(LMent_Debug PRIVATE DEBUG_BUILD SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)
target_compile_options(LMent_Debug PRIVATE -O0 -g -std=c++17)
target_link_libraries(LMent_Debug sfml-graphics sfml-window sfml-system)

# Setup for Release Build
add_executable(LMent ${SOURCES})
target_compile_definitions(LMent PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO)
target_compile_options(LMent PRIVATE -O2 -std=c++17)
target_link_libraries(LMent sfml-graphics sfml-window sfml-system)
