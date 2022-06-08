add_executable(test test.cpp)
target_link_libraries(test gtest_main atomjson pthread)