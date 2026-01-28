cmake_minimum_required(VERSION 3.16)

project(StationExToolbox VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RAPIDXML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/rapidxml/include)
set(ARGS_INCLUDE_DIR     ${CMAKE_SOURCE_DIR}/lib/args/include)

add_subdirectory(StationExToolbox)

