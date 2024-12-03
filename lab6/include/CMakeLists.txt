cmake_minimum_required(VERSION 3.26)

add_library(game INTERFACE)

target_sources(
	game
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/Factory.h
	${CMAKE_CURRENT_SOURCE_DIR}/Observer.h
	${CMAKE_CURRENT_SOURCE_DIR}/Visitor.h
	${CMAKE_CURRENT_SOURCE_DIR}/Character.h
	${CMAKE_CURRENT_SOURCE_DIR}/World.h
)

target_include_directories(
	game
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}
)