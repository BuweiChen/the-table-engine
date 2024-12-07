cmake_minimum_required(VERSION 3.4)
project(pybind11_test)

# Set path to pybind11
set(PYBIND11_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11)

# Add pybind11 subdirectory with explicit path
if(NOT EXISTS ${PYBIND11_ROOT}/CMakeLists.txt)
    message(FATAL_ERROR "pybind11 submodule not found. Please run: git submodule update --init")
endif()

# Find Python before pybind11
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Add pybind11
add_subdirectory(${PYBIND11_ROOT} ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Create the module
pybind11_add_module(example_module example.cpp)

# Optional: Copy test script to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_example.py
               ${CMAKE_CURRENT_BINARY_DIR}/test_example.py COPYONLY)