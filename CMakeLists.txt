cmake_minimum_required (VERSION 2.8)

project (KronikiAndarii)

set (EXECUTABLE_OUTPUT_PATH "${KronikiAndarii_SOURCE_DIR}")
set (CMAKE_CXX_FLAGS "-Wall -std=c++11")
set (CMAKE_BUILD_TYPE Debug)
message (Current\ build\ type:\ ${CMAKE_BUILD_TYPE})

find_package (Qt5 COMPONENTS Core Gui Widgets)
include_directories (${Qt5Widgets_INCLUDE_DIRS} ${KronikiAndarii_SOURCE_DIR}/src)

add_subdirectory (src)
