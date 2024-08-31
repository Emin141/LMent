cmake_minimum_required(VERSION 3.10)
project(LMent)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set C standard for C files
set(CMAKE_C_STANDARD 99) 

# Setup include directories
include_directories(include third_party/include)

# Source files
file(GLOB_RECURSE COMMON_SOURCES ${CMAKE_SOURCE_DIR}/src/common/*.cpp)
file(GLOB CLIENT_SOURCES ${CMAKE_SOURCE_DIR}/src/client/*.cpp)
file(GLOB SERVER_SOURCES ${CMAKE_SOURCE_DIR}/src/server/*.cpp)
set(CLIENT_MAIN ${CMAKE_SOURCE_DIR}/src/client/main.cpp)
set(SERVER_MAIN ${CMAKE_SOURCE_DIR}/src/server/main.cpp)

# Create client target
add_executable(Client ${CLIENT_MAIN} ${COMMON_SOURCES} ${CLIENT_SOURCES})
add_executable(Client_Debug ${CLIENT_MAIN} ${COMMON_SOURCES} ${CLIENT_SOURCES})
set_target_properties(Client_Debug PROPERTIES OUTPUT_NAME "Client_Debug")

# Create server target
add_executable(Server ${SERVER_MAIN} ${COMMON_SOURCES} ${SERVER_SOURCES})
add_executable(Server_Debug ${SERVER_MAIN} ${COMMON_SOURCES} ${SERVER_SOURCES})
set_target_properties(Server_Debug PROPERTIES OUTPUT_NAME "Server_Debug")

# Set compiler flags
target_compile_options(Client_Debug PRIVATE -O0 -g -Werror -Wall -fPIC -DDEBUG_BUILD)
target_compile_options(Server_Debug PRIVATE -O0 -g -Werror -Wall -fPIC -DDEBUG_BUILD)

# Link libraries (e.g., SFML)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(Client sfml-system sfml-window sfml-graphics sfml-network sfml-audio dl)
target_link_libraries(Server sfml-system sfml-network)
target_link_libraries(Client_Debug sfml-system sfml-window sfml-graphics sfml-network sfml-audio dl)
target_link_libraries(Server_Debug sfml-system sfml-network)

