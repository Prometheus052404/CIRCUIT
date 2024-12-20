# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude -I/usr/include/gtest

# Project name
TARGET = DCSimulator

# Directories
SRCDIR = src
OBJDIR = obj
TESTDIR = tests

# Google Test configuration
GTEST_LIBS = -L/usr/lib -lgtest -lgtest_main -pthread

# Source files and object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp

OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
OBJECTS := $(patsubst main.cpp, $(OBJDIR)/main.o, $(OBJECTS))

# Test-specific files excluding main.cpp from the test build process
TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
TEST_SOURCES := $(filter-out $(TESTDIR)/test_main.cpp, $(TEST_SOURCES))
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SOURCES))

# Phony targets
.PHONY: all clean test rebuild

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(GTEST_LIBS)

# Compile each .cpp file into .o file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main.cpp in the root directory
$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)
	
# Compile test files into .o files
$(OBJDIR)/%.o: $(TESTDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Unit test target & Build test binary (exclude main.cpp for the test build)
test: $(TEST_OBJECTS) | $(OBJDIR)
	$(CXX) $(TEST_OBJECTS) -o $(OBJDIR)/test_bin $(GTEST_LIBS)
	./$(OBJDIR)/test_bin

# Clean up build files, i.e. Clean target to remove object files and the executable
clean:
	rm -rf $(OBJDIR) $(TARGET) $(OBJDIR)/test_bin
# ADD "test_output.txt" to the list of files to be removed if using the standard (commented out) test target.

rebuild: clean all
