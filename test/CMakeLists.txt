find_package(Catch2 REQUIRED)

add_executable(tdd)

target_sources(tdd
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/tdd.cpp)

target_include_directories(tdd
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tdd
	PUBLIC
	Catch2::Catch2WithMain
	parsium)

include(CTest)
include(Catch)
catch_discover_tests(tdd)
