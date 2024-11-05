cmake_minimum_required(VERSION 3.22)
project(oop CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


add_executable(${CMAKE_PROJECT_NAME}_exe src/main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}_exe PRIVATE include)
#

enable_testing()

add_executable(Array_tests tests/array_tests.cpp)
target_include_directories(Array_tests PRIVATE include)

add_executable(Figure_tests tests/figure_tests.cpp)
target_include_directories(Figure_tests PRIVATE include)

target_link_libraries(Array_tests PRIVATE GTest::GTest)
target_link_libraries(Figure_tests PRIVATE GTest::GTest)


add_test(NAME ${CMAKE_PROJECT_NAME}_tests COMMAND ${CMAKE_PROJECT_NAME}_tests)