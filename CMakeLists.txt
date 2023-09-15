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

include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Modules ${SOURCES})

target_link_libraries(Modules GTest::gtest_main)
include(GoogleTest)
gtest_add_tests(
    TARGET      Modules
    TEST_LIST   ModulesTest
)

gtest_discover_tests(Modules)
