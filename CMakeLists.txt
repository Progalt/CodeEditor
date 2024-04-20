cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0076 NEW)


project(CodeEditor)




find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

find_package(fmt)

add_executable(CodeEditor)

set_target_properties(
    CodeEditor PROPERTIES 
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(TARGET SDL2::SDL2main)
    target_link_libraries(CodeEditor PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(CodeEditor PRIVATE SDL2::SDL2 fmt::fmt)


add_subdirectory("src")
