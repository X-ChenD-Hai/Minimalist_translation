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

find_package(Qt6 COMPONENTS Widgets Network REQUIRED) # Qt COMPONENTS

file(GLOB ui_srcs src/ui/*.cpp
    src/ui/*.ui
    src/ui/*.rc
)
file(GLOB trans_srcs src/lib/core/*.cpp
    src/lib/core/engines/*.cpp
)
file(GLOB resource_srcs src/lib/resourse/*.cpp
    resource/res.qrc
)

# Specify MSVC UTF-8 encoding
include_directories(
    src
)

set(trans_lib trans)
set(resource_lib resource)

add_library(${trans_lib}d SHARED ${trans_srcs})
add_library(${resource_lib} SHARED ${resource_srcs})
include_directories(${trans_lib}d PRIVATE src/lib/core)
add_executable(${PROJECT_NAME}d

    # WIN32 # If you need a terminal for debug, please comment this statement
    ${ui_srcs}
    test/main.cpp
)
target_compile_definitions(${trans_lib}d PRIVATE -DLIBRARY)

target_link_libraries(${trans_lib}d PRIVATE Qt6::Widgets PUBLIC Qt6::Network) # Qt6 Shared Library
target_link_libraries(${resource_lib} PRIVATE Qt6::Widgets) # Qt6 Shared Library
target_link_libraries(${PROJECT_NAME}d PRIVATE Qt6::Widgets PRIVATE ${trans_lib}d PRIVATE ${resource_lib}) # Qt6 Shared Library