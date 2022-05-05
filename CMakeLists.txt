cmake_minimum_required (VERSION 3.8)

project ("MyJsonParser - AtomJson C Version")

add_library(atomjson atomjson.cpp)
add_executable(atom_test test.cpp)
target_link_libraries(atomjson_test atomjson)