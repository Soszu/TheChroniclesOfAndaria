cmake_minimum_required (VERSION 2.8)

project (TheChroniclesOfAndaria)

find_package (Qt5 COMPONENTS Core Gui Widgets Network)
include_directories (${Qt5Widgets_INCLUDE_DIRS} ${TheChroniclesOfAndaria_SOURCE_DIR}/src)

set (EXECUTABLE_OUTPUT_PATH "${TheChroniclesOfAndaria_BINARY_DIR}/bin")
set (LIBRARY_OUTPUT_PATH "${TheChroniclesOfAndaria_BINARY_DIR}/lib")
set (CMAKE_CXX_FLAGS "-Wall -std=c++11")
set (CMAKE_BUILD_TYPE Debug)
message (Current\ build\ type:\ ${CMAKE_BUILD_TYPE})

add_subdirectory (src)

install (DIRECTORY data DESTINATION "${EXECUTABLE_OUTPUT_PATH}")
