add_executable(parsium_example_sandbox)

target_sources(parsium_example_sandbox
    PRIVATE
    "sandbox/main.cpp")

target_include_directories(parsium_example_sandbox
    PRIVATE
    .)

target_link_libraries(parsium_example_sandbox
    PRIVATE
    parsium)
