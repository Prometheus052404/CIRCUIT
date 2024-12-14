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
include_directories(${PROJECT_SOURCE_DIR}/include)

# Set the output directories for the compiled binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create a list of source files from the 'src/' and 'main.cpp'
file(GLOB_RECURSE SRC_FILES 
    src/*.cpp 
    main.cpp
)

# Add the executable for the project
add_executable(DigitalLogicSimulator ${SRC_FILES})

# Testing configuration
enable_testing()

# Copy test files to build directory
configure_file(${PROJECT_SOURCE_DIR}/test/test_input.txt ${CMAKE_BINARY_DIR}/test_input.txt COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test/expected_output.txt ${CMAKE_BINARY_DIR}/expected_output.txt COPYONLY)

# Add test
add_test(
    NAME IntegrationTest
    COMMAND ${CMAKE_COMMAND} -E bash -c "$<TARGET_FILE:${PROJECT_NAME}> < test_input.txt > test_output.txt && diff test_output.txt expected_output.txt"
) 
# Installation for the binary (optional, installs it to /usr/local/bin)
install(TARGETS DigitalLogicSimulator DESTINATION bin)


