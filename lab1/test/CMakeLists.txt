cmake_minimum_required(VERSION 3.10)

cmake_policy(PUSH)

enable_testing()

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
	cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(sources
	"${CMAKE_CURRENT_SOURCE_DIR}/lab_test.cc"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

add_executable(
	lab-test
	${sources}
)

if(MSVC)
		target_compile_options(
			lab-test
				PRIVATE /W4
				PRIVATE /MP
				PRIVATE /WX
		)
endif()

target_link_libraries(
	lab-test
	GTest::gtest_main
	GTest::gmock_main
	utils
)

include(GoogleTest)
gtest_discover_tests(lab-test)

set_target_properties(gtest_main PROPERTIES FOLDER "vendor")
set_target_properties(gtest PROPERTIES FOLDER "vendor")
set_target_properties(gmock_main PROPERTIES FOLDER "vendor")
set_target_properties(gmock PROPERTIES FOLDER "vendor")

cmake_policy(POP)