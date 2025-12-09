cmake_minimum_required(VERSION 4.2.0)
project(lab2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Array src/main.cpp)

target_include_directories(Array PUBLIC
    include
)

target_compile_features(Array PUBLIC)

# Избавляемся от стрёмных макросов винды
add_compile_definitions(NOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_compile_options(-Wall -Wextra -Wpedantic)

## Добавляем GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  array_test
  tests/array.cpp
)
target_link_libraries(
  array_test
  GTest::gtest_main
)
target_include_directories(array_test PUBLIC
    include
)

include(GoogleTest)
gtest_add_tests(TARGET array_test
    SOURCES tests/array.cpp
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)
