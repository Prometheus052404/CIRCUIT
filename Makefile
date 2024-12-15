# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude -I/usr/include/gtest
LDFLAGS = -L/usr/lib -lgtest -lgtest_main -pthread

# Project name
TARGET = DCSimulator

# Directories
SRCDIR = src
OBJDIR = obj
TESTDIR = test

TEST_SRC = $(TESTDIR)/test.cpp		
TEST_BIN = $(OBJDIR)/test.o

# Google Test configuration
GTEST_LIBS = -L/usr/lib -lgtest -lgtest_main -pthread

# Source files and object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp

OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
OBJECTS := $(patsubst main.cpp, $(OBJDIR)/main.o, $(OBJECTS))
# Exclude main.cpp from the test build process
TEST_SOURCES = $(wildcard $(SRCDIR)/*.cpp)
TEST_OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(TEST_SOURCES))
TEST_OBJECTS += $(OBJDIR)/test.o

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

# Compile test.cpp in the test directory
$(OBJDIR)/test.o: $(TESTDIR)/test.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Unit test target (exclude main.cpp for the test build)
test: $(OBJDIR)/test_bin
	./$(OBJDIR)/test_bin

# Build test binary
$(OBJDIR)/test_bin: $(TEST_OBJECTS) | $(OBJDIR)
	$(CXX) $(TEST_OBJECTS) -o $(OBJDIR)/test_bin $(LDFLAGS)

# Clean up build files, i.e. Clean target to remove object files and the executable
clean:
	rm -rf $(OBJDIR) $(TARGET) $(OBJDIR)/test_bin
# ADD "test_output.txt" to the list of files to be removed if using the standard (commented out) test target.

rebuild: clean all
