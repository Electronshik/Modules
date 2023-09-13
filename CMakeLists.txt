cmake_minimum_required(VERSION 3.16.3)

project(Modules)
set(PROJECT_BINARY_DIR build)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${PROJECT_BINARY_DIR})
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)


file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/*.ixx",
	"${PROJECT_SOURCE_DIR}/*.cpp",
)

include_directories(
	${CMAKE_SOURCE_DIR},
)

# add_link_options(-fcoroutines)

add_executable(Modules ${SOURCES})
