cmake_minimum_required(VERSION 3.4)
project(pybind11_test)

# Clear any cached Python variables
unset(Python3_EXECUTABLE CACHE)
unset(Python3_ROOT_DIR CACHE)
unset(PYTHON_EXECUTABLE CACHE)
unset(PYTHONINTERP_FOUND CACHE)
unset(PYTHON_VERSION_STRING CACHE)

# Find Python first
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Force pybind11 to use the same Python we just found
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE} CACHE INTERNAL "")
set(PYBIND11_PYTHON_VERSION ${Python3_VERSION} CACHE INTERNAL "")

# Add pybind11
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Create the module
pybind11_add_module(example_module example.cpp)

# Print the Python being used (for debugging)
message(STATUS "Using Python: ${Python3_EXECUTABLE}")
message(STATUS "Python version: ${Python3_VERSION}")