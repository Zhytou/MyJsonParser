cmake_minimum_required(VERSION 3.14)

project ("MyJsonParser - AtomJson")

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(atomjson Atomjson.cpp String.cpp Array.cpp Object.cpp)
add_executable(test test.cpp)
target_link_libraries(test gtest_main atomjson pthread)

include(GoogleTest)
gtest_discover_tests(test)