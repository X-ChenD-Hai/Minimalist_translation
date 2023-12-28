cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(MTranslation LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "d:/worktools/design/Qt/6.6.1/mingw_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt6 COMPONENTS Widgets REQUIRED) # Qt COMPONENTS
file(GLOB srcs src/ui/*.cpp src/ui/*.ui src/ui/*.rc resource/res.qrc)
file(GLOB lib_srcs src/lib/*cpp)

# Specify MSVC UTF-8 encoding
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
include_directories(
    src
)

set(trans_lib trans_lib)
add_library(${trans_lib}d SHARED ${lib_srcs})

add_executable(${PROJECT_NAME}d
    # WIN32 # If you need a terminal for debug, please comment this statement
    ${srcs}
    test/main.cpp
)

target_link_libraries(${trans_lib}d PRIVATE Qt6::Widgets) # Qt6 Shared Library
target_link_libraries(${PROJECT_NAME}d PRIVATE Qt6::Widgets PRIVATE ${trans_lib}d) # Qt6 Shared Library