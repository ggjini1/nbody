# Top-level Makefile

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -I../src

# Source and build paths
SRC_DIR := ../src
SRC_FILES := $(SRC_DIR)/main.cpp
OBJ_FILES := main.o

# Output binary
TARGET := main

# Default target
all: $(TARGET)

# Compile object file
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link final binary
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean
clean:
	rm -f *.o $(TARGET)