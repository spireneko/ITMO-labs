#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>

#include "dice.hpp"

const char* DIR_NAME = "stats";

const size_t NUMBER_OF_MEASUREMENTS = 10000;

int main() {
    if (!std::filesystem::exists(DIR_NAME)) {
        std::filesystem::create_directory(DIR_NAME);
    }

    std::ofstream file(std::filesystem::path(DIR_NAME) / "1d6.txt");
    Dice dice_instance = Dice(6, 1);
    for (size_t i = 0; i < NUMBER_OF_MEASUREMENTS; i++) {
        file << dice(dice_instance, 0) << "\n";
    }
    file.close();

    file.open(std::filesystem::path(DIR_NAME) / "2d6.txt");
    dice_instance = Dice(6, 2);
    for (size_t i = 0; i < NUMBER_OF_MEASUREMENTS; i++) {
        file << dice(dice_instance, 0) << "\n";
    }
    file.close();

    file.open(std::filesystem::path(DIR_NAME) / "3d6.txt");
    dice_instance = Dice(6, 3);
    for (size_t i = 0; i < NUMBER_OF_MEASUREMENTS; i++) {
        file << dice(dice_instance, 0) << "\n";
    }
    file.close();

    file.open(std::filesystem::path(DIR_NAME) / "1d10.txt");
    dice_instance = Dice(10, 1);
    for (size_t i = 0; i < NUMBER_OF_MEASUREMENTS; i++) {
        file << dice(dice_instance, 0) << "\n";
    }
    file.close();

    file.open(std::filesystem::path(DIR_NAME) / "2d10.txt");
    dice_instance = Dice(10, 2);
    for (size_t i = 0; i < NUMBER_OF_MEASUREMENTS; i++) {
        file << dice(dice_instance, 0) << "\n";
    }
    file.close();

    file.open(std::filesystem::path(DIR_NAME) / "3d10.txt");
    dice_instance = Dice(10, 3);
    for (size_t i = 0; i < NUMBER_OF_MEASUREMENTS; i++) {
        file << dice(dice_instance, 0) << "\n";
    }
    file.close();

    return 0;
}

int dice(const Dice& dice_instance, int32_t modifier = 0) {
    for (int32_t roll = 0; roll < dice_instance.get_amount(); roll++) {
        modifier += get_random(1, dice_instance.get_faces());
    }

    return modifier;
}

int dice(const Dice* dices, size_t size, int32_t modifier = 0) {
    for (size_t i = 0; i < size; i++) {
        modifier += dice(dices[i]);
    }

    return modifier;
}
