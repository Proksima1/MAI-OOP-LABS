cmake_minimum_required(VERSION 3.22)
project(oop CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


add_executable(${CMAKE_PROJECT_NAME}_exe src/main.cpp src/classes/binary.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}_exe PRIVATE include)


enable_testing()
add_executable(${CMAKE_PROJECT_NAME}_tests tests/tests.cpp src/classes/binary.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}_tests PRIVATE GTest::GTest)
target_include_directories(${CMAKE_PROJECT_NAME}_tests PRIVATE include)


add_test(NAME ${CMAKE_PROJECT_NAME}_tests COMMAND ${CMAKE_PROJECT_NAME}_tests)