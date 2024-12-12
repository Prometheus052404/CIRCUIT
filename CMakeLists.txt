# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(DigitalLogicSimulator VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler warnings for quality
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Include the headers from the 'include' directory
include_directories(include)

# Set the output directories for the compiled binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create a list of source files from the 'src/' and 'main.cpp'
file(GLOB_RECURSE SRC_FILES 
    src/*.cpp 
    main.cpp
)

# Add the executable for the project
add_executable(DigitalLogicSimulator ${SRC_FILES})

# Optionally, include tests (optional subdirectory for test files)
add_subdirectory(test)

# Installation for the binary (optional, installs it to /usr/local/bin)
install(TARGETS DigitalLogicSimulator DESTINATION bin)
