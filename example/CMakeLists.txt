add_library(parsium_example_common INTERFACE)

target_include_directories(parsium_example_common
	INTERFACE
	..)

add_subdirectory(mckeeman)
