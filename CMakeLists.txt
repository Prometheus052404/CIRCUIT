cmake_minimum_required(VERSION 3.10)
project(DigitalLogicSimulator VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build type to Release by default if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
file(GLOB SOURCES 
    "src/*.cpp"
    "main.cpp"
)

# Main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Enable testing
enable_testing()

# Create test directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test)

# Copy test files
configure_file(${PROJECT_SOURCE_DIR}/test/test_input.txt 
               ${CMAKE_BINARY_DIR}/test/test_input.txt 
               COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test/expected_output.txt 
               ${CMAKE_BINARY_DIR}/test/expected_output.txt 
               COPYONLY)

# Create a shell script to run the test (no diff in Release mode)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    file(WRITE ${CMAKE_BINARY_DIR}/test/run_test.sh
    "#!/bin/bash\n"
    "dos2unix test_output.txt expected_output.txt\n"
    "${CMAKE_BINARY_DIR}/DigitalLogicSimulator < test_input.txt > test_output.txt\n"
    "echo 'Test completed successfully.'\n"
    "exit 0\n")
else()
    # Create a shell script for Debug mode with diff
    file(WRITE ${CMAKE_BINARY_DIR}/test/run_test.sh
    "#!/bin/bash\n"
    "dos2unix test_output.txt expected_output.txt\n"
    "${CMAKE_BINARY_DIR}/DigitalLogicSimulator < test_input.txt > test_output.txt\n"
    "diff test_output.txt expected_output.txt\n"
    "exit $?\n")
endif()

# This block of code is commented out. Just use this to debug more deeply (if any errors occur) the test script.
if(FALSE)
    # Create a shell script to run the test with debug output, Method 2
    # Replace all the below code with the else() block above if needed to debug extensively.
    file(WRITE ${CMAKE_BINARY_DIR}/test/run_test.sh
    "#!/bin/bash
    set -x  # Enable debug output
    echo 'Current directory:' $(pwd)
    echo 'Contents of current directory:' $(ls)
    echo 'Contents of test directory:' $(ls)
    echo 'Executable path:' ${CMAKE_BINARY_DIR}/DigitalLogicSimulator
    echo 'Executable exists:' $(test -f ${CMAKE_BINARY_DIR}/DigitalLogicSimulator && echo 'yes' || echo 'no')
    dos2unix test_output.txt expected_output.txt

    ${CMAKE_BINARY_DIR}/DigitalLogicSimulator < test_input.txt > test_output.txt
    TEST_EXIT_CODE=$?
    echo 'Program exit code:' $TEST_EXIT_CODE

    echo 'Contents of test_input.txt:'
    cat test_input.txt
    echo '---'
    echo 'Contents of test_output.txt:'
    cat test_output.txt
    echo '---'
    echo 'Contents of expected_output.txt:'
    cat expected_output.txt
    echo '---'
    echo 'Diff result:'
    diff test_output.txt expected_output.txt
    exit $?
    ")

    message("This will not be executed.")

  endif()
  

# Make the shell script executable
file(CHMOD ${CMAKE_BINARY_DIR}/test/run_test.sh
PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

# Add the test
add_test(
    NAME IntegrationTest
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test
    COMMAND ${CMAKE_BINARY_DIR}/test/run_test.sh
)

# Test properties
set_tests_properties(IntegrationTest PROPERTIES
    TIMEOUT 30
    WILL_FAIL FALSE
)

# Install targets
install(TARGETS ${PROJECT_NAME} DESTINATION bin)