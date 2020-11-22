cmake_minimum_required(VERSION 3.1.0)

project(MonopolyApp)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")

set(BUILD_TESTS 1)

add_subdirectory(Monopoly)
if(BUILD_TESTS)
    add_subdirectory(gtest)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

    add_subdirectory(Tests)
endif()