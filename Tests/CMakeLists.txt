cmake_minimum_required(VERSION 3.4)
project(pybind11_test)

# Get Python version from the actual interpreter
execute_process(
    COMMAND python3 -c "import sys; print(sys.executable)"
    OUTPUT_VARIABLE PYTHON_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Force CMake to use this Python
set(Python3_EXECUTABLE ${PYTHON_PATH})

# Find Python components
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Add pybind11
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Create the module
pybind11_add_module(example_module example.cpp)

# Print for verification
message(STATUS "Python Path: ${PYTHON_PATH}")
message(STATUS "Python Version: ${Python3_VERSION}")

#test