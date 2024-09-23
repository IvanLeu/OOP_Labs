cmake_minimum_required(VERSION 3.26)

set(sources 
	"${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp"
)

add_library(
	utils
	INTERFACE
	${sources}
)

target_include_directories(
	utils
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
