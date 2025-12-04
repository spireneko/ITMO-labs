#pragma once

#include <cstdint>
#include <optional>
#include <random>

// Won't stop until get user's valid answer or stop signal
std::optional<int32_t> get_answer_from_user(const char* question);

std::optional<int32_t> read_integer(std::istream& stream);

bool random_bool(double probability);

bool is_file_exists(const std::string& name);

std::string to_lower_ru(const std::string& str);

template <typename T>
T get_random(T min, T max) {
    static_assert(std::is_arithmetic_v<T>, "Template parameter must be an arithmetic type (integral or floating point)");

    static std::random_device rd;
    static std::mt19937 gen(rd());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(gen);
    } else {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(gen);
    }
}
