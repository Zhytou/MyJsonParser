add_executable(simple simple.cpp)
target_link_libraries(simple atomjson)

add_executable(value value.cpp)
target_link_libraries(value atomjson)

add_executable(customizedStringify customizedStringify.cpp)
target_link_libraries(customizedStringify atomjson)