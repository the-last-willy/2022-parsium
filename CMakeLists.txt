cmake_minimum_required(VERSION 3.21)
project(parsium_private)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

find_package(Catch2 REQUIRED)

if(MSVC)
    add_compile_options(/std:c++17 /W4)
elseif()
    add_compile_options(-std=c++17 -Wall)
endif()

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(test)
