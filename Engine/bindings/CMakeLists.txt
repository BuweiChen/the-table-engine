cmake_minimum_required(VERSION 3.10)
project(engine_bindings)

# Find Python
set(Python3_FIND_STRATEGY LOCATION)
set(Python3_FIND_FRAMEWORK LAST)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Add pybind11
set(PYBIND11_FINDPYTHON ON)
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)

# Find SDL2 and SDL2_mixer
find_package(SDL2 REQUIRED)
# find_package(SDL2_mixer REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
)

# Create the binding module
pybind11_add_module(engine engine_bindings.cpp)

# Link against engine library, SDL2, and SDL2_mixer
target_link_libraries(engine PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/libengine.a
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    -lSDL2_ttf
)

# Print Python info for debugging
message(STATUS "Building with Python: ${Python3_EXECUTABLE}")