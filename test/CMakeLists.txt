# Disables default CTest targets.
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

include(Catch)
include(CTest)

################################################################################

add_executable(parsium_test_common_container_tree)

target_link_libraries(parsium_test_common_container_tree
	PRIVATE
	parsium_example_common
	common_libraries
	Catch2::Catch2)

target_include_directories(parsium_test_common_container_tree
	PRIVATE
	..)

target_sources(parsium_test_common_container_tree
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/common/container/tree/main.cpp)

catch_discover_tests(parsium_test_common_container_tree)

################################################################################

add_executable(parsium_test_json)

target_link_libraries(parsium_test_json
	PRIVATE
	parsium_example_common
	common_libraries
	Catch2::Catch2)

target_include_directories(parsium_test_json
	PRIVATE
	..)

target_sources(parsium_test_json
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/json/main.cpp)

catch_discover_tests(parsium_test_json)

################################################################################

add_executable(parsium_test_mckeeman)

target_link_libraries(parsium_test_mckeeman
	PRIVATE
	parsium_example_common
	common_libraries
	Catch2::Catch2)

target_include_directories(parsium_test_mckeeman
	PRIVATE
	..)

target_sources(parsium_test_mckeeman
    PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/mckeeman/tests.cpp)

catch_discover_tests(parsium_test_mckeeman)

################################################################################
