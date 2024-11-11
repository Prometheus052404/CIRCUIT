# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Project name and target
TARGET = DigitalCircuitSimulator

# List of all .cpp files in the directory (assumes .cpp files are in the root directory)
SOURCES = $(wildcard *.cpp)

# Automatically generated list of .o files based on .cpp file names
OBJECTS = $(SOURCES:.cpp=.o)

# Default target to build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule for creating .o files from .cpp files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJECTS) $(TARGET)
