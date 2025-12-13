cmake_minimum_required(VERSION 4.2.0)
project(lab4)

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
add_executable(dice src/main.cpp)

target_include_directories(dice PUBLIC
    include
)
