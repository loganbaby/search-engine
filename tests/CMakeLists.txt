cmake_minimum_required(VERSION 3.22)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SrcFiles
        ${SOURCE_DIR}/InvertedIndex.cpp
        ${SOURCE_DIR}/SearchServer.cpp
        ${SOURCE_DIR}/ConverterJSON.cpp
        )

set(TestsFiles
        TestsInvertedIndexFunctionality.cpp
        TestsCaseSearchServer.cpp
        )

add_executable(GtestTests ${TestsFiles} ${SrcFiles})
target_link_libraries(GtestTests nlohmann_json::nlohmann_json GTest::gtest_main)
include(GoogleTest)
target_link_libraries(GtestTests GTest::gtest_main)

target_include_directories(GtestTests PUBLIC ${MY_INCLUDE_DIR})
gtest_discover_tests(GtestTests)