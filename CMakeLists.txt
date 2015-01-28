cmake_minimum_required (VERSION 2.8)

project (TheChroniclesOfAndaria)
set (TheChroniclesOfAndaria_VERSION_MAJOR 2)
set (TheChroniclesOfAndaria_VERSION_MINOR 0)

find_package (Qt5 COMPONENTS Core Gui Widgets Network)
include_directories (${Qt5Widgets_INCLUDE_DIRS} ${TheChroniclesOfAndaria_SOURCE_DIR}/src)

set (EXECUTABLE_OUTPUT_PATH "${TheChroniclesOfAndaria_BINARY_DIR}/bin")
set (LIBRARY_OUTPUT_PATH "${TheChroniclesOfAndaria_BINARY_DIR}/lib")
set (CMAKE_CXX_FLAGS "-Wall -std=c++11")

add_subdirectory (src)

install (DIRECTORY data DESTINATION "${EXECUTABLE_OUTPUT_PATH}")
