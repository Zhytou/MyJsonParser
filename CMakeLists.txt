cmake_minimum_required(VERSION 3.14)

project ("MyJsonParser - AtomJson C Version")

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(atomjson atomjson.cpp)
add_executable(atom_test test.cpp)
target_link_libraries(atomjson_test atomjson)