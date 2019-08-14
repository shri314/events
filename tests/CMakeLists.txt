cmake_minimum_required (VERSION 3.5)

add_executable(
   basic_test
   main.cpp
   basic_test.cpp
)

target_link_libraries(
   basic_test
   gtest
)

add_test(basicTest basic_test)
