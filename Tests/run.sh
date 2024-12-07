#!/bin/bash

# Get the current Python executable
PYTHON_EXE=$(which python3)

# Clean previous build
rm -rf build
mkdir build
cd build

# Export Python paths for CMake to find
export Python3_ROOT_DIR=$(dirname $(dirname $PYTHON_EXE))

# Configure and build
cmake ..
make

# Run the test with the same Python
$PYTHON_EXE ../test_example.py