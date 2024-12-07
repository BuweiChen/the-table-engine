cmake_minimum_required(VERSION 3.14)
project(pybind11_test)

set(CMAKE_CXX_STANDARD 17)

# Add pybind11 submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/../extern/pybind11 extern/pybind11)

# Create the Python module
pybind11_add_module(example example.cpp)
