cmake_minimum_required(VERSION 3.26)

set(sources 
	"${CMAKE_CURRENT_SOURCE_DIR}/Eleven.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Eleven.cpp"
)

add_library(
	task-lib
	INTERFACE
	${sources}
)

target_include_directories(
	task-lib
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)