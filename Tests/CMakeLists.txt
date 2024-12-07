cmake_minimum_required(VERSION 3.4)
project(pybind11_test)

# Find Python first
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Add pybind11
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Create the module
pybind11_add_module(example_module example.cpp)

# Print the Python being used (for debugging)
message(STATUS "Using Python: ${Python3_EXECUTABLE}")