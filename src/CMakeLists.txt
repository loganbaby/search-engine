cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME search-engine-skillbox)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(JSON_DIR ${CMAKE_SOURCE_DIR}/json)
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/res)

add_executable(${PROJECT_NAME}
        main.cpp
        InvertedIndex.cpp
        ConverterJSON.cpp
        SearchServer.cpp
        ${INCLUDE_DIR}/ConverterJSON.h
        ${INCLUDE_DIR}/exceptions.h
        ${INCLUDE_DIR}/InvertedIndex.h
        ${INCLUDE_DIR}/SearchServer.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

file(COPY ${JSON_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${RESOURCE_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})