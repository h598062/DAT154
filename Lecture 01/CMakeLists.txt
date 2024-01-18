cmake_minimum_required(VERSION 3.17)
project(Lecture01)

set(CMAKE_CXX_STANDARD 14)

# Add your source files here
add_executable(Lecture01Demo myprog1/myprog1.cpp myprog1/math.cpp)

# Specify the configurations
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Lecture01Demo)

# Visual Studio configurations
set_property(TARGET Lecture01Demo PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Configuration for Debug|x64
if (CMAKE_GENERATOR_PLATFORM MATCHES "x64")
    # Add any additional configuration specific to Debug|x64
endif()

# Configuration for Debug|x86
if (CMAKE_GENERATOR_PLATFORM MATCHES "Win32")
    # Add any additional configuration specific to Debug|x86
endif()

# Configuration for Release|x64
if (CMAKE_GENERATOR_PLATFORM MATCHES "x64")
    # Add any additional configuration specific to Release|x64
endif()

# Configuration for Release|x86
if (CMAKE_GENERATOR_PLATFORM MATCHES "Win32")
    # Add any additional configuration specific to Release|x86
endif()
