cmake_minimum_required(VERSION 4.2.0)
project(lab1)

add_executable(Hammurabi src/main.cpp)

target_include_directories(Hammurabi PUBLIC
    include
)

target_compile_features(Hammurabi PUBLIC cxx_std_17)

# Избавляемся от стрёмных макросов винды
add_compile_definitions(NOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_compile_options(-Wall -Wextra -Wpedantic)
