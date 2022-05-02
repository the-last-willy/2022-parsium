
################################################################################

add_library(common_libraries INTERFACE)

target_include_directories(common_libraries
	INTERFACE
	.)

################################################################################

add_executable(generator)

target_link_libraries(generator
	PUBLIC
	common_libraries)

target_sources(generator
	PRIVATE
	generator/main.cpp)

################################################################################

add_executable(sandbox_fsm)

target_link_libraries(sandbox_fsm
	PUBLIC
	common_libraries)

target_sources(sandbox_fsm
	PRIVATE
	sandbox/fsm/generated.cpp)

################################################################################

add_subdirectory(sandbox/json)
add_subdirectory(sandbox/json2)
add_subdirectory(sandbox/mckeeman)
