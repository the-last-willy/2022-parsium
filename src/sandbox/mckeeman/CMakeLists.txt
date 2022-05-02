
add_library(parsium_sandbox_mckeeman)

target_link_libraries(parsium_sandbox_mckeeman
	PUBLIC
	common_libraries
	)

target_sources(parsium_sandbox_mckeeman
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	)
