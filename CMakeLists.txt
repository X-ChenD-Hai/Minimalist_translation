cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(MTranslation LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "d:/worktools/design/Qt/6.6.1/mingw_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(Qt6 COMPONENTS Widgets Network Sql REQUIRED) # Qt COMPONENTS

# global
include_directories(src)
file(COPY lib/QHotkey/bin/libQHotkey.dll DESTINATION ${CMAKE_BINARY_DIR}/../bin)

# resource_lib
set(resource_lib resource)

file(GLOB resource_srcs
    src/resourse/*.cpp
    resource/res.qrc
)
add_library(${resource_lib} SHARED ${resource_srcs})

target_link_libraries(${resource_lib} PRIVATE Qt6::Widgets)

# trans_lib
set(trans_lib trans)

file(GLOB trans_srcs src/core/*.cpp
    src/core/engines/*.cpp
)

add_library(${trans_lib} SHARED ${trans_srcs})

target_compile_definitions(${trans_lib} PRIVATE -DLIBRARY)

target_include_directories(${trans_lib} PRIVATE src/core)

target_link_libraries(${trans_lib} PUBLIC Qt6::Network PUBLIC Qt6::Sql)

# project
file(GLOB ui_srcs src/ui/*.cpp
    src/ui/*.ui
    src/ui/*.rc
    lib/frameless/framelesswindow.cpp
)

add_executable(${PROJECT_NAME}
    WIN32 # If you need a terminal for debug, please comment this statement
    ${ui_srcs}
    test/main.cpp
)

target_link_directories(${PROJECT_NAME} PRIVATE lib/QHotkey/bin/)
target_include_directories(${PROJECT_NAME} PRIVATE ./
    PRIVATE include)

target_compile_definitions(${PROJECT_NAME} PRIVATE -DQHOTKEY_LIB)
target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Widgets
    PRIVATE Dwmapi.lib
    PRIVATE QHotkey
    PRIVATE ${trans_lib}
    PRIVATE ${resource_lib})

# test1
add_executable(
    test1
    test/test1.cpp
)
target_compile_definitions(test1 PRIVATE -DQHOTKEY_LIB)
target_include_directories(test1 PRIVATE testi)
target_link_directories(test1 PRIVATE lib/QHotkey/bin)
target_link_libraries(test1
    PRIVATE Qt6::Widgets
    Qt6::Sql
    )
