cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME search-engine-skillbox)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

# nlohmann_json including
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)

# googletest including
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.12.1)

include_directories(${PROJECT_NAME} ${INCLUDE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

FetchContent_MakeAvailable(json googletest)