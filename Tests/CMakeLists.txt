cmake_minimum_required(VERSION 3.4)
project(pybind11_test)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

pybind11_add_module(example_module example.cpp)