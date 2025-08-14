cmake_minimum_required(VERSION 3.10)

project(GlobalReplicationExample)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the root directory so we can use paths like "GlobalReplication/Public/..."
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Gather all the source files for the library
file(GLOB_RECURSE LIB_SOURCES "GlobalReplication/Private/*.cpp")

# Add the library
add_library(GlobalReplication STATIC ${LIB_SOURCES})

# Add the executable
add_executable(Example main.cpp)

# Link the executable to our library
target_link_libraries(Example GlobalReplication)
