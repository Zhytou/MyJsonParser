cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 11)

project(MyJsonParser:AtomJson
        VERSION 2019.1
        DESCRIPTION "My Simple JSON Parser @https://github.com/Zhytou/MyJsonParser"
        LANGUAGES C CXX
        )

#Gtest
configure_file("${PROJECT_SOURCE_DIR}/thirdparties/gtest_CMakeLists.txt.in" googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # don't override our compiler/linker options when building gtest
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src" "${CMAKE_BINARY_DIR}/googletest-build")

# includes
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# subdirectories
add_subdirectory(${PROJECT_SOURCE_DIR}/example)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/test)