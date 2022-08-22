cmake_minimum_required(VERSION 3.15)

project(parsium)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

if(MSVC)
	add_compile_options(/W3 /std:c++20)
else() # Clang, GCC
	add_compile_options(-Wall -std=c++20)
endif()

add_subdirectory(example)
add_subdirectory(src)
add_subdirectory(test)
