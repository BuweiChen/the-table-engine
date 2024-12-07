cmake_minimum_required(VERSION 3.4)
project(pybind11_test)

# Clear any cached Python variables to force fresh detection
unset(Python3_EXECUTABLE CACHE)
unset(Python3_ROOT_DIR CACHE)
unset(Python3_ROOT CACHE)
unset(Python_ROOT_DIR CACHE)
unset(Python_ROOT CACHE)

# Hint CMake to prefer the Python in PATH
set(Python3_FIND_STRATEGY LOCATION)
set(Python3_FIND_REGISTRY NEVER) # Ignore Windows registry
set(Python3_FIND_FRAMEWORK NEVER) # Ignore macOS frameworks

# Find Python with these preferences
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Add pybind11
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Create the module
pybind11_add_module(example_module example.cpp)

# Print the Python being used (for diagnostic purposes)
message(STATUS "Using Python: ${Python3_EXECUTABLE}")
message(STATUS "Python version: ${Python3_VERSION}")