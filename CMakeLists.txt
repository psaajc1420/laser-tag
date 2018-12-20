# version of cmake
cmake_minimum_required(VERSION 3.9.0)

# name of the project
project(laser-tag)

# set flags for compiler
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

#Bring the headers from the include directory
set(lasertag_build_include_dirs
    "${CMAKE_SOURCE_DIR}"
    "include/laser-tag")
include_directories(${lasertag_build_include_dirs})

file(GLOB SOURCES
    "src/laser_tag.cpp"
    "src/laser_tag_list.cpp"
    "src/player.cpp"
    "src/team.cpp"
    "include/laser-tag/strings/ds_string.cpp"
)

# Add all files in src directory
add_executable(main.out tests/main.cpp ${SOURCES})

set_target_properties(main.out
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

