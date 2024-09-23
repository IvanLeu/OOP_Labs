cmake_minimum_required(VERSION 3.26)

set(sources 
	"${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp"
)

add_library(
	lab1
	INTERFACE
	${sources}
)

target_include_directories(
	lab1
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)
