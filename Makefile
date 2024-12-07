# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Wall -Wextra -pedantic

# Project name
TARGET = DCSimulator

# Directories
SRCDIR = src
OBJDIR = obj

# Source files and object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
OBJECTS := $(patsubst main.cpp, $(OBJDIR)/main.o, $(OBJECTS))

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

# Rule for creating .o files from .cpp files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files, i.e. Clean target to remove object files and the executable
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Test step
test:
	@echo "Running tests..."
	./$(TARGET) < tests/test_input.txt > tests/test_output.txt
	diff -q tests/test_output.txt tests/expected_output.txt && echo "All tests passed!" || echo "Tests failed!"

# Phony targets
.PHONY: all clean

