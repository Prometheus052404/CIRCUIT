# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Wall -Wextra -pedantic

# Project name
TARGET = DCSimulator

# Directories
SRCDIR = src
OBJDIR = obj
TESTDIR = test

# Source files and object files
SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
OBJECTS := $(patsubst main.cpp, $(OBJDIR)/main.o, $(OBJECTS))

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
test: $(TARGET)
	@echo "Running tests..."
	@cp $(TESTDIR)/test_input.txt ./test_input.txt
	@cp $(TESTDIR)/expected_output.txt ./expected_output.txt
	./$(TARGET) < test_input.txt > test_output.txt
	diff test_output.txt expected_output.txt && echo "All tests passed!" || echo "Tests failed!"
	@rm -f test_input.txt expected_output.txt test_output.txt

# Clean up build files, i.e. Clean target to remove object files and the executable
clean:
	rm -rf $(OBJDIR) $(TARGET) test_output.txt

rebuild: clean all
