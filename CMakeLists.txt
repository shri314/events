cmake_minimum_required (VERSION 3.10.2)

###################################

include(ExternalProject)

ExternalProject_Add(
   GTest
   URL "https://github.com/google/googletest/archive/release-1.8.1.tar.gz"
   URL_MD5 "2e6fbeb6a91310a16efe181886c59596"
   CMAKE_GENERATOR ${gen}
   CMAKE_ARGS
      -DBUILD_SHARED_LIBS:BOOL=ON
      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/3rdpty/gtest
)

ExternalProject_Add(
   Date
   URL "https://github.com/HowardHinnant/date/archive/v2.4.1.tar.gz"
   URL_MD5 "54d9dd9d5ac32214d3cbe8cc80bbccf2"
   CMAKE_GENERATOR ${gen}
   CMAKE_ARGS
      -DCMAKE_CXX_STANDARD:STRING=17
      -DBUILD_SHARED_LIBS:BOOL=ON
      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/3rdpty/date
)

ExternalProject_Add(
   Json
   URL "https://github.com/nlohmann/json/archive/v3.7.0.tar.gz"
   URL_MD5 "4755f892ee7770ecee31296b29d43fef"
   CMAKE_GENERATOR ${gen}
   CMAKE_ARGS
      -DCMAKE_CXX_STANDARD:STRING=17
      -DBUILD_SHARED_LIBS:BOOL=ON
      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/3rdpty/json
)

###################################

project(foo-example LANGUAGES CXX)

add_compile_options(-fPIC -std=c++17 -Wall -Wextra -Wno-unknown-pragmas -Werror "$<$<CONFIG:RELEASE>:-flto>" "$<$<CONFIG:DEBUG>:-O0>" "$<$<CONFIG:DEBUG>:-g3>")

#set( CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard whose features are requested.")

link_directories(
   ${CMAKE_SOURCE_DIR}/3rdpty/date/lib
   ${CMAKE_SOURCE_DIR}/3rdpty/gtest/lib
   ${CMAKE_SOURCE_DIR}/3rdpty/json/lib
)

include_directories(
   ${CMAKE_SOURCE_DIR}/3rdpty/date/include
   ${CMAKE_SOURCE_DIR}/3rdpty/gtest/include
   ${CMAKE_SOURCE_DIR}/3rdpty/json/include
   include
)

enable_testing()
add_custom_target(check ${CMAKE_CTEST_COMMAND})

add_subdirectory(src)
add_subdirectory(tests)
