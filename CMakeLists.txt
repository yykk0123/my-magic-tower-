#Define the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(MAGIC_TOWER)

# Set the C++ standard
set(CMAKE_CXX_STANDDARD 11)

# Add source files to the project
add_executable(${PROJECT_NAME}
  main.cpp
  elements.cpp
  operation.cpp
)
