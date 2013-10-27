cmake_minimum_required (VERSION 2.8)

project (Planszowka)

set (EXECUTABLE_OUTPUT_PATH "${Planszowka_SOURCE_DIR}")

# -DCMAKE_BUILD_TYPE=Release
set(CMAKE_BUILD_TYPE Debug)
message(Current\ build\ type:\ ${CMAKE_BUILD_TYPE})

set( CMAKE_CXX_FLAGS "-Wall -std=c++11 " )
#set( CMAKE_CXX_FLAGS_DEBUG "-g" "-Wall" )
#set( CMAKE_CXX_FLAGS_RELEASE "-O3 ")

find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})
add_definitions (${QT_DEFINITIONS})

include_directories (${Planszowka_SOURCE_DIR}/src)

add_subdirectory (src)
