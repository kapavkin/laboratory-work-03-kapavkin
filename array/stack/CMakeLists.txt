cmake_minimum_required(VERSION 3.0)

project(stack)

set(HEADERS stack.h ../array.h)
set(SOURCES stack.cpp ../array.cpp)

add_library(stack SHARED ${HEADERS} ${SOURCES})

target_include_directories(stack PUBLIC ${CMAKE_SOURCE_DIR}/array)
target_include_directories(stack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
