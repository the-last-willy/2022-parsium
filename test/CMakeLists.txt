# Disables default CTest targets.
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

include(CTest)
include(Catch)

################################################################################

add_executable(json_test)

target_link_libraries(json_test
	PRIVATE
	json_format

	common_libraries

	Catch2::Catch2)

target_sources(json_test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/json/unit.cpp)

catch_discover_tests(json_test)

################################################################################
