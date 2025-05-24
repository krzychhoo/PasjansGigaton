# Ustawienie minimalnej wersji narzędzia CMake
cmake_minimum_required(VERSION 3.16)
# Set the project name and version

project(PasjansGigaton VERSION 0.2)


# Specify the C++ standard

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Add the executable

add_executable(PasjansGigaton src/main.cpp)
