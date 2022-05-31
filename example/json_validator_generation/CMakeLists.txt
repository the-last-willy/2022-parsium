
add_executable(parsium_example_json_parser_generation)

target_link_libraries(parsium_example_json_parser_generation
	PRIVATE
	common_libraries
	parsium_example_common
	)

target_sources(parsium_example_json_parser_generation
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	)
