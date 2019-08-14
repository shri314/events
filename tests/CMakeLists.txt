cmake_minimum_required (VERSION 3.5)

add_executable(
   foo_test
   ${PROJECT_SOURCE_DIR}/src/foo.cpp
   main.cpp
   foo_test.cpp
)

target_link_libraries(
   foo_test
   gtest
)

add_test(fooTest foo_test)
