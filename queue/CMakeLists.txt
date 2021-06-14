cmake_minimum_required(VERSION 3.0)

project(queue)

set(HEADERS queue.h)
set(SOURCES queue.cpp)

add_library(queue SHARED ${HEADERS} ${SOURCES})

target_include_directories(queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
