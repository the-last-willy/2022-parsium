
################################################################################

add_library(json_format)

target_link_libraries(json_format
    PUBLIC
	common_libraries
)

target_sources(json_format
    PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/format.cpp
)

################################################################################

add_executable(sandbox_json)

target_link_libraries(sandbox_json
    PUBLIC
	json_format
)

target_sources(sandbox_json
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

################################################################################
