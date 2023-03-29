cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME unit-testing)
project(${PROJECT_NAME})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR}/src)
include_directories(../include ${GTEST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
        "../src/ConverterJSON.cpp"
        "../src/InvertedIndex.cpp"
        "../src/SearchServer.cpp"
        "InvertedIndexTest.cpp"
        "SearchServerTest.cpp")

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)