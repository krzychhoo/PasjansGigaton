# Ustawienie minimalnej wersji narzędzia CMake
cmake_minimum_required(VERSION 3.16)
# Set the project name and version

project(PasjansGigaton VERSION 0.3)


# Specify the C++ standard

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(nowide CONFIG REQUIRED)


# Add the executable

add_executable(PasjansGigaton src/main.cpp )
target_link_libraries(PasjansGigaton PRIVATE nowide::nowide)
install(TARGETS PasjansGigaton DESTINATION ${PROJECT_SOURCE_DIR}/bin)