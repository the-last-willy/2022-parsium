cmake_minimum_required(VERSION 3.21)
project(parser_gen)

################################################################################

add_library(common_libraries INTERFACE)

target_include_directories(common_libraries
    INTERFACE
        src
)

################################################################################

add_executable(generator)

target_link_libraries(generator
    PUBLIC
        common_libraries
)

target_sources(generator
    PRIVATE
        src/generator/main.cpp
)

################################################################################

add_executable(sandbox_fsm)

target_link_libraries(sandbox_fsm
    PUBLIC
        common_libraries
)

target_sources(sandbox_fsm
    PRIVATE
        src/sandbox/fsm/main.cpp
)
