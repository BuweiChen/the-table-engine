#!/bin/bash

# Get the current Python executable and force CMake to use it
PYTHON_EXE=$(which python3)
echo "Using Python: $PYTHON_EXE"

# Clean previous build
rm -rf build
mkdir build
cd build

# Configure and build with forced Python path
CMAKE_PREFIX_PATH=$(dirname $(dirname $PYTHON_EXE)) cmake -DPython3_EXECUTABLE=$PYTHON_EXE ..
make

# Run the test with the same Python
$PYTHON_EXE ../test_example.py