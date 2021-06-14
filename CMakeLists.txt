cmake_minimum_required(VERSION 3.0)

project(laboratory-work-03-kapavkin)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(MAIN main.cpp)

enable_testing()

add_executable(main ${MAIN})

add_subdirectory(array)
add_subdirectory(list)
add_subdirectory(queue)
add_subdirectory(tree)

target_link_libraries(main
  array
  list
  queue
  tree
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(main)
