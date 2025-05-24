PYTHON_CONFIG := /usr/bin/python3-config  # or /usr/local/bin/python3-config

# Compiler settings
CXX := g++
PYTHON_CONFIG := python3-config
PYTHON_PREFIX := /opt/homebrew/opt/python@3.13
NUMPY_INCLUDE := /opt/homebrew/lib/python3.13/site-packages/numpy/core/include

CXXFLAGS := -std=c++17 -Wall \
  -I./src \
  -I./external \
  -I$(PYTHON_PREFIX)/Frameworks/Python.framework/Versions/3.13/include/python3.13 \
  -DWITHOUT_NUMPY

LDFLAGS := -L$(PYTHON_PREFIX)/Frameworks/Python.framework/Versions/3.13/lib \
  -lpython3.13

# Source and object files
SRC := src/main.cpp
OBJ := build/main.o
TARGET := build/main

# Default target
all: $(TARGET)

# Ensure build directory exists
build:
	mkdir -p build

# Compile object file
$(OBJ): $(SRC) | build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Clean build artifacts
clean:
	rm -rf build