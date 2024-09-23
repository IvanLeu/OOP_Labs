cmake_minimum_required(VERSION 3.10)

project(lab1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED)

include(FetchContent)

add_subdirectory("include")
add_library(lab::utils ALIAS utils)

add_subdirectory("src")

enable_testing()
add_subdirectory("test")