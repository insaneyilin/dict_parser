cmake_minimum_required(VERSION 2.8)

project(dict_parser)

add_definitions(-std=c++11)

find_package(GTest REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${GTEST_INCLUDE_DIRS})
link_directories(${GTEST_LIBRARY_DIRS})

file(GLOB DICT_PARSER_SRCS "*.cpp")

add_library(${PROJECT_NAME} ${DICT_PARSER_SRCS})

add_subdirectory(test)
add_subdirectory(demo)
