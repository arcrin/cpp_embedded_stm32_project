cmake_minimum_required(VERSION 3.15.0)

# Set the project name
project(MyCppProject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(MyCppProject main.cpp)