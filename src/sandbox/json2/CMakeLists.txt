
################################################################################

add_library(file_format_json)

target_link_libraries(file_format_json
    PUBLIC
	common_libraries
)

target_sources(file_format_json
    PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/format.cpp
)

################################################################################

add_executable(sandbox_json_2)

target_link_libraries(sandbox_json_2
    PRIVATE
	file_format_json
)

target_sources(sandbox_json_2
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

################################################################################
