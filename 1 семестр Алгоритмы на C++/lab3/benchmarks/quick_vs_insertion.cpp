#include <cstdint>
#include <fstream>
#include <random>
#include <string>

#include <nanobench.h>

#include "sort.hpp"

int main() {
    std::ofstream insertion_file("insertion_results.txt");
    std::ofstream quick_file("quick_results.txt");
    std::vector<double> insertion_times;
    std::vector<double> quick_times;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1000000);

    for (size_t size = 0; size <= 100; ++size) {
        std::vector<int32_t> data(size);
        for (size_t i = 0; i < size; ++i) {
            data[i] = dist(gen);
        }

        // Тестируем сортировку вставками
        {
            std::string test_name = "insertion_sort_" + std::to_string(size);

            auto bench = ankerl::nanobench::Bench();
            bench.minEpochIterations(30000);
            bench.run(test_name, [&] {
                std::vector<int> copy = data;

                insertion_sort(copy.data(), copy.data() + copy.size(), [](int32_t a, int32_t b) { return a < b; });
                ankerl::nanobench::doNotOptimizeAway(copy);
            });
            bench.render("{{median(elapsed)}} ", insertion_file);
        }

        // Тестируем быструю сортировку
        {
            std::string test_name = "quick_sort_" + std::to_string(size);

            auto bench = ankerl::nanobench::Bench();
            bench.minEpochIterations(10000);
            bench.run(test_name, [&] {
                std::vector<int> copy = data;

                sort(copy.data(), copy.data() + copy.size(), [](int a, int b) { return a < b; });
                ankerl::nanobench::doNotOptimizeAway(copy);
            });
            bench.render("{{median(elapsed)}} ", quick_file);
        }
    }

    insertion_file.close();
    quick_file.close();
    return 0;
}
