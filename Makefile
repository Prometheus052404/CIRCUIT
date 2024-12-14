# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Wall -Wextra -pedantic

# # Vcpkg Google Test paths 
# VCPKG_ROOT = C:/DevTools/vcpkg
# GTEST_INCLUDE = $(VCPKG_ROOT)/installed/x64-windows/include
# GTEST_LIB = $(VCPKG_ROOT)/installed/x64-windows/lib

# Project name
TARGET = DCSimulator

# Directories
SRCDIR = src
OBJDIR = obj
TESTDIR = test

TEST_SRC = $(TESTDIR)/test.cpp
TEST_BIN = $(OBJDIR)/test_bin

# Google Test configuration
# GTEST_LIBS = -L$(GTEST_LIB) -lgtest -lgtest_main -pthread
GTEST_LIBS = -lgtest -lgtest_main -pthread
# Compiler flags with Google Test include path
# CXXFLAGS += -I$(GTEST_INCLUDE)

# Source files and object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp

OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
OBJECTS := $(patsubst main.cpp, $(OBJDIR)/main.o, $(OBJECTS))
# Exclude main.cpp from the test build process
TEST_SOURCES = $(wildcard $(SRCDIR)/*.cpp)
TEST_SOURCES := $(filter-out $(SRCDIR)/main.cpp, $(TEST_SOURCES))

# Phony targets
.PHONY: all clean test rebuild

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile each .cpp file into .o file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main.cpp in the root directory
$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Test step
# test: $(TARGET)
# 	@echo "Running tests..."
# 	@cp $(TESTDIR)/test_input.txt ./test_input.txt
# 	@cp $(TESTDIR)/expected_output.txt ./expected_output.txt
# 	./$(TARGET) < test_input.txt > $(TESTDIR)/test_output.txt
# 	dos2unix $(TESTDIR)/test_output.txt expected_output.txt
# 	diff $(TESTDIR)/test_output.txt expected_output.txt && echo "All tests passed!" || echo "Tests failed!"
# 	@rm -f test_input.txt expected_output.txt $(TESTDIR)/test_output.txt

# Unit test target (exclude main.cpp for the test build)
test: $(OBJDIR)/test_bin
	./$(OBJDIR)/test_bin

# Build test binary
$(OBJDIR)/test_bin: $(TEST_SOURCES) $(OBJECTS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -o $(OBJDIR)/test_bin $(TEST_SOURCES) $(OBJECTS) $(GTEST_LIBS)

# Clean up build files, i.e. Clean target to remove object files and the executable
clean:
	rm -rf $(OBJDIR) $(TARGET) $(OBJDIR)/test_bin
# ADD "test_output.txt" to the list of files to be removed if using the standard (commented out) test target.

rebuild: clean all
