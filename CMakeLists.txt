cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0076 NEW)


project(CodeEditor)

add_subdirectory("glfw")
add_subdirectory("fmt")



find_package(fmt)

add_executable(CodeEditor)

set_target_properties(
    CodeEditor PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(CodeEditor glfw fmt::fmt)


add_subdirectory("src")
