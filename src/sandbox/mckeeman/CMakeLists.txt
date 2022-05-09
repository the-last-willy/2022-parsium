
add_executable(parsium_sandbox_mckeeman)

target_link_libraries(parsium_sandbox_mckeeman
	PRIVATE
	common_libraries
	)

target_sources(parsium_sandbox_mckeeman
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	)
