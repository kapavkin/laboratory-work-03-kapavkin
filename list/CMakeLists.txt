cmake_minimum_required(VERSION 3.0)

project(list)

set(HEADERS list.h)
set(SOURCES list.cpp)

add_library(list SHARED ${HEADERS} ${SOURCES})

target_include_directories(list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
