cmake_minimum_required(VERSION 4.2.0)
project(lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем поддержку разных конфигураций
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Флаги для Debug сборки
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -Wpedantic -g -O0")
# Флаги для Release сборки
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -Wpedantic -O3 -DNDEBUG")

# Избавляемся от стрёмных макросов винды
add_compile_definitions(NOMINMAX)

# Избавляемся от ворнингов, что мы не используем secure функции винды
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Основной экзешник
add_executable(sort src/main.cpp)

target_include_directories(sort PUBLIC
    include
)

# Экзешник для тестов
add_executable(
  sort_test
  tests/sort.cpp
)

target_include_directories(sort_test PUBLIC
    include
)

# Экзешник бенчмарка
add_executable(
  quick_vs_insertion_bench
  benchmarks/quick_vs_insertion.cpp
)

target_include_directories(quick_vs_insertion_bench PUBLIC
    include
)

# Автоматическая закачка зависемостей
include(FetchContent)

## Добавляем GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(
  sort_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_add_tests(TARGET sort_test
    SOURCES tests/sort.cpp
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)

## Добавляем nanobench
FetchContent_Declare(
    nanobench
    GIT_REPOSITORY https://github.com/martinus/nanobench.git
    GIT_TAG v4.3.11
    GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(nanobench)

target_link_libraries(quick_vs_insertion_bench PRIVATE nanobench)
