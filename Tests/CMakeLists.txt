cmake_minimum_required(VERSION 3.10)
project(pybind11_test)

# Don't search for Python, use what's provided
set(Python3_FIND_STRATEGY LOCATION)
set(Python3_FIND_FRAMEWORK LAST)  # On macOS, prefer Brew/System Python over Framework Python

# Find Python components with exact executable
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Force pybind11 to use our Python
set(PYBIND11_FINDPYTHON ON)
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})

# Add pybind11
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Create the module
pybind11_add_module(example_module example.cpp)

# Print for verification
message(STATUS "Building with Python: ${Python3_EXECUTABLE}")