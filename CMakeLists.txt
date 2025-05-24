# Ustawienie minimalnej wersji narzędzia CMake
cmake_minimum_required(VERSION 3.16)
# Set the project name and version

project(PasjansGigaton VERSION 0.1)


# Specify the C++ standard

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)


# Add the executable

add_executable(PasjansGigaton src/main.cpp)
