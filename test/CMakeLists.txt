# Disables default CTest targets.
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

include(Catch)
include(CTest)

################################################################################

add_executable(parsium_test_json)

target_link_libraries(parsium_test_json
	PRIVATE
	parsium_example_common
	common_libraries
	Catch2::Catch2)

target_sources(parsium_test_json
    PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/json/tests.cpp)

catch_discover_tests(parsium_test_json)

################################################################################
