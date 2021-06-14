cmake_minimum_required(VERSION 3.0)

project(array)

set(HEADERS array.h)
set(SOURCES array.cpp)

add_library(array SHARED ${HEADERS} ${SOURCES})

add_subdirectory(stack)

target_link_libraries(array stack)

target_include_directories(array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
