cmake_minimum_required (VERSION 2.8)

project (Planszowka)

set (EXECUTABLE_OUTPUT_PATH "${Planszowka_BINARY_DIR}")

find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})
add_definitions (${QT_DEFINITIONS})

include_directories (${Planszowka_SOURCE_DIR}/src)

add_subdirectory (src)
