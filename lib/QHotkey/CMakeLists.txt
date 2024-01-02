cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(MTranslation LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "d:/worktools/design/Qt/6.6.1/mingw_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(Qt6 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS

add_library(QHotkey SHARED ./qhotkey.cpp ./qhotkey_win.cpp)
target_compile_definitions(QHotkey PRIVATE -DQHOTKEY_LIB -DQHOTKEY_LIB_BUILD)
target_link_libraries(QHotkey PRIVATE Qt6::Widgets)