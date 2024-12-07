cmake_minimum_required(VERSION 3.10)  # Update to remove deprecation warning
project(pybind11_test)

# Prevent pybind11 from searching for Python again
set(PYBIND11_FINDPYTHON ON)

# Find Python first
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Tell pybind11 to use our Python
set(Python_EXECUTABLE ${Python3_EXECUTABLE})
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})
set(Python_LIBRARIES ${Python3_LIBRARIES})
set(Python_INCLUDE_DIRS ${Python3_INCLUDE_DIRS})

# Add pybind11
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Create the module
pybind11_add_module(example_module example.cpp)

message(STATUS "Using Python executable: ${Python3_EXECUTABLE}")
message(STATUS "Using Python libraries: ${Python3_LIBRARIES}")
message(STATUS "Using Python include dirs: ${Python3_INCLUDE_DIRS}")