cmake_minimum_required(VERSION 4.4)

# CMake 4.4's import std support must be enabled before compiler detection.
if(NOT DEFINED CMAKE_EXPERIMENTAL_CXX_IMPORT_STD)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
        "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
endif()

project(CowString LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_MODULE_STD ON)

add_library(CowString src/CowString.cpp src/SymbolModifier.cpp)
target_sources(CowString
    PUBLIC
        FILE_SET CXX_MODULES FILES
            src/CowString.cppm
            src/CowStringInterface.cppm
            src/SymbolModifier.cppm
)

include(CTest)
if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    add_executable(CowStringTests tests/CowStringTests.cpp)
    target_link_libraries(CowStringTests PRIVATE CowString GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(CowStringTests)
endif()

option(COWSTRING_BUILD_BENCHMARKS "Build Google Benchmark benchmarks" OFF)
if(COWSTRING_BUILD_BENCHMARKS)
    find_package(benchmark CONFIG REQUIRED)
    add_executable(CowStringBenchmarks benchmarks/CowStringBenchmarks.cpp)
    target_link_libraries(CowStringBenchmarks
        PRIVATE CowString benchmark::benchmark_main)
endif()
