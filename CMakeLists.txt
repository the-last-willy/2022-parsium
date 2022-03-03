cmake_minimum_required(VERSION 3.22)
project(parser_gen)

add_executable(generator)

target_include_directories(generator
PUBLIC
    src
)

target_sources(generator
PRIVATE
    src/generator/main.cpp
)
