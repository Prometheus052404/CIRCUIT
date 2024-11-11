# Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(DigitalCircuitSimulator VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the header files directory
include_directories(include)

# Add source files
set(SOURCES
    main.cpp
    NANDGateIC.cpp
    NORGateIC.cpp
    XORGateIC.cpp
    XORGateIC.cpp
    ANDGateIC.cpp
    ORGateIC.cpp
    NOTGateIC.cpp
    # Add other source files as needed
)

# Create the executable from the source files
add_executable(DigitalCircuitSimulator ${SOURCES})
