cmake_minimum_required(VERSION 3.4)
project(pybind11_test)

# Ensure Python 3
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Add pybind11
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Create the module
pybind11_add_module(example_module example.cpp)

# Copy the test script to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test_example.py
               ${CMAKE_CURRENT_BINARY_DIR}/test_example.py COPYONLY)

# Optional: Add a test target
add_custom_target(run_tests
    COMMAND Python3::Interpreter ${CMAKE_CURRENT_BINARY_DIR}/test_example.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS example_module
)