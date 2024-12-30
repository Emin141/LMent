cmake_minimum_required(VERSION 3.10)
project(LMent)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# Include directories
include_directories(source third_party/include)

# Locate SFML (required on both platforms)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# Gather common source files
file(GLOB_RECURSE COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/source/common/*.cpp
)

# Gather client source files
file(GLOB CLIENT_SOURCES
    ${CMAKE_SOURCE_DIR}/source/client/*.cpp
    ${CMAKE_SOURCE_DIR}/source/client/ui/*.cpp
)

# Gather server source files
file(GLOB SERVER_SOURCES
    ${CMAKE_SOURCE_DIR}/source/server/*.cpp
)

# Platform-specific settings
if(WIN32)
    # Windows-specific settings
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    # Add Client and Server executables
    add_executable(Client ${COMMON_SOURCES} ${CLIENT_SOURCES})
    add_executable(Server ${COMMON_SOURCES} ${SERVER_SOURCES})

    # Link SFML libraries
    target_link_libraries(Client sfml-system sfml-window sfml-graphics sfml-network sfml-audio lz4)
    target_link_libraries(Server sfml-system sfml-network)

    # Add Debug Builds
    add_executable(Client_Debug ${COMMON_SOURCES} ${CLIENT_SOURCES})
    add_executable(Server_Debug ${COMMON_SOURCES} ${SERVER_SOURCES})
    target_link_libraries(Client_Debug sfml-system sfml-window sfml-graphics sfml-network sfml-audio dl lz4)
    target_link_libraries(Server_Debug sfml-system sfml-network)
    set_target_properties(Client_Debug PROPERTIES OUTPUT_NAME "Client_Debug")
    set_target_properties(Server_Debug PROPERTIES OUTPUT_NAME "Server_Debug")

    target_compile_options(Client_Debug PRIVATE /Od /DEBUG /Wall /DDEBUG_BUILD)
    target_compile_options(Server_Debug PRIVATE /Od /DEBUG /Wall /DDEBUG_BUILD)

else()
    # Linux-specific settings
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    # Add Client and Server executables
    add_executable(Client ${COMMON_SOURCES} ${CLIENT_SOURCES})
    add_executable(Server ${COMMON_SOURCES} ${SERVER_SOURCES})

    # Link SFML libraries
    target_link_libraries(Client sfml-system sfml-window sfml-graphics sfml-network sfml-audio dl lz4)
    target_link_libraries(Server sfml-system sfml-network)

    # Add Debug Builds
    add_executable(Client_Debug ${COMMON_SOURCES} ${CLIENT_SOURCES})
    add_executable(Server_Debug ${COMMON_SOURCES} ${SERVER_SOURCES})
    target_link_libraries(Client_Debug sfml-system sfml-window sfml-graphics sfml-network sfml-audio dl lz4)
    target_link_libraries(Server_Debug sfml-system sfml-network)
    set_target_properties(Client_Debug PROPERTIES OUTPUT_NAME "Client_Debug")
    set_target_properties(Server_Debug PROPERTIES OUTPUT_NAME "Server_Debug")
    target_compile_options(Client_Debug PRIVATE -O0 -g -Werror -Wall -fPIC -DDEBUG_BUILD)
    target_compile_options(Server_Debug PRIVATE -O0 -g -Werror -Wall -fPIC -DDEBUG_BUILD)
endif()
