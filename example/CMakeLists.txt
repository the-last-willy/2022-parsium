add_library(parsium_example_common INTERFACE)

target_include_directories(parsium_example_common
	INTERFACE
	../src)

add_subdirectory(json_validator_generation)
add_subdirectory(mckeeman)

################################################################################

add_executable(parsium_example_sandbox)

target_sources(parsium_example_sandbox
	PRIVATE
	sandbox/main.cpp)

target_link_libraries(parsium_example_sandbox
	PRIVATE
	common_libraries
	parsium_example_common)

################################################################################

add_executable(parsium_example_sandbox_json)

target_sources(parsium_example_sandbox_json
	PRIVATE
	sandbox/json/main.cpp)

target_link_libraries(parsium_example_sandbox_json
	PRIVATE
	common_libraries
	parsium_example_common)
