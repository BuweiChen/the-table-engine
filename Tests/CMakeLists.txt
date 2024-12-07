cmake_minimum_required(VERSION 3.4)
project(pybind11_test)

# Clear any existing Python variables that might be cached
unset(Python3_EXECUTABLE CACHE)
unset(Python3_INCLUDE_DIR CACHE)
unset(Python3_LIBRARY CACHE)
unset(PYTHON_EXECUTABLE CACHE)
unset(PYTHON_INCLUDE_DIR CACHE)
unset(PYTHON_LIBRARY CACHE)

# Find Python first, and be explicit about it
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Print Python paths for debugging
message(STATUS "Python3_EXECUTABLE: ${Python3_EXECUTABLE}")
message(STATUS "Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")

# Set pybind11 to use the Python we just found
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})
set(PYBIND11_PYTHON_VERSION 3)

# Add pybind11
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Create the module
pybind11_add_module(example_module example.cpp)

# Copy test script to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_example.py
               ${CMAKE_CURRENT_BINARY_DIR}/test_example.py COPYONLY)