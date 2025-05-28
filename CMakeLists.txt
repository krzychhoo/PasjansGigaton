# Ustawienie minimalnej wersji narzędzia CMake
cmake_minimum_required(VERSION 3.16)

# Nazwa projektu
project(PasjansGigaton VERSION 1.0)


# Ustawienie standardu c++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Komenda wymagana, aby clangd widziało nagłówki
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Importowanie biblioteki nowide
find_package(nowide CONFIG REQUIRED)

# Definicja pliku wykonywalnego i linkowanie bibliotek
add_executable(PasjansGigaton src/main.cpp )
target_link_libraries(PasjansGigaton PRIVATE nowide::nowide)

# Folder docelowy do instalacji
install(TARGETS PasjansGigaton DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(FILES $<TARGET_RUNTIME_DLLS:PasjansGigaton> DESTINATION ${PROJECT_SOURCE_DIR}/bin)
