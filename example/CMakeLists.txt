add_executable(simple simple.cpp)
target_link_libraries(simple atomjson)

add_executable(value value.cpp)
target_link_libraries(value atomjson)

add_executable(parse_stringify parse_stringify.cpp)
target_link_libraries(parse_stringify atomjson)