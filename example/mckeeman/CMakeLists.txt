
add_executable(parsium_example_mckeeman)

target_link_libraries(parsium_example_mckeeman
	PRIVATE
	common_libraries
	parsium_example_common
	)

target_sources(parsium_example_mckeeman
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	)
