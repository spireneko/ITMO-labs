#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#ifdef _WIN32
    #include <windows.h>
#endif

#include "functions.hpp"

const char* BAD_END_MESSAGE = "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. Теперь вы вынуждены влачить жалкое существование в изгнании";
const char* HARD_HAND_END_MESSAGE = "Вы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем";
const char* PRETTY_GOOD_END = "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова";
const char* BEST_END = "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше";
const char* BYE_BYE_MESSAGE = "До скорой встречи!";

const char* SAVE_FILE_PATH = "save.txt";

void setup_console() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

int main() {
    setup_console();

    std::string input;
    bool need_to_load_save = false;
    if (std::filesystem::exists(SAVE_FILE_PATH)) {
        std::cout << "Хотите продолжить там, где закончили? (yes/no) " << std::endl;
        bool has_valid_answer = false;
        while (!has_valid_answer) {
            std::getline(std::cin, input);
            input = to_lower_ru(input);
            if (input == "yes") {
                has_valid_answer = true;
                need_to_load_save = true;
            } else if (input == "no") {
                has_valid_answer = true;
                need_to_load_save = false;
            }
        }
    }
    int32_t people_amount = 100;
    int32_t wheal_bushels = 2800;
    int32_t acres_of_land = 1000;
    int32_t round = 1;
    bool was_plague = false;
    int32_t people_died = 0;
    int32_t people_arrived = 0;
    int32_t bushels_harvested = 0;
    int32_t bushels_eaten_by_rats = 0;
    int32_t old_wheal_per_acre = 0;

    // Mean value of dead to all people proportions
    double P = 0.0;

    while (round <= 10) {
        int32_t acre_price = get_random(17, 26);
        int32_t wheal_per_acre = get_random(1, 6);
        double proportion_eaten_by_rats = get_random(0.0, 0.07);

        if (need_to_load_save) {
            std::ifstream file(SAVE_FILE_PATH, std::ios::in);
            file >> people_amount >> wheal_bushels >> acres_of_land >> round >> was_plague >> people_died >> people_arrived >> bushels_harvested >> bushels_eaten_by_rats >>
                old_wheal_per_acre >> P >> acre_price >> wheal_per_acre >> proportion_eaten_by_rats;
            need_to_load_save = false;
        }

        {
            // truncate file
            if (std::filesystem::exists(SAVE_FILE_PATH)) {
                std::filesystem::resize_file(SAVE_FILE_PATH, 0);
            }

            std::fstream file(SAVE_FILE_PATH);
            file << people_amount << " " << wheal_bushels << " " << acres_of_land << " " << round << " " << was_plague << " " << people_died << " " << people_arrived << " "
                 << bushels_harvested << " " << bushels_eaten_by_rats << " " << old_wheal_per_acre << " " << P << " " << acre_price << " " << wheal_per_acre << " "
                 << proportion_eaten_by_rats;
        }

        // Input values
        int32_t acres_to_buy;
        int32_t acres_to_sell;
        int32_t bushels_to_eat;
        int32_t acres_to_plant;

        std::cout << "Мой повелитель, соизволь поведать тебе\n";
        std::cout << "\tв году " << round << " твоего высочайшего правления\n";

        if (people_died > 0 || people_arrived > 0) {
            std::cout << "\t";
        }
        if (people_died > 0) {
            std::cout << people_died << " человек умерли с голоду";
        }
        if (people_died > 0 && people_arrived > 0) {
            std::cout << ", и ";
        }
        if (people_arrived > 0) {
            std::cout << people_arrived << " человек прибыли в наш великий город";
        }
        if (people_died > 0 || people_arrived > 0) {
            std::cout << ";\n";
        }

        std::cout << "\t";
        if (was_plague) {
            std::cout << "Чума уничтожила половину населения;\n";
        } else {
            std::cout << "Твои подданные здоровы как никогда прежде;\n";
        }

        std::cout << "\tНаселение города сейчас составляет " << people_amount << " человек;\n";

        if (bushels_harvested > 0) {
            std::cout << "\tМы собрали " << bushels_harvested << " бушелей пшеницы, по " << old_wheal_per_acre << " бушеля с акра;\n";
        }

        std::cout << "\t";
        if (bushels_eaten_by_rats > 0) {
            std::cout << "Крысы истребили " << bushels_eaten_by_rats << " бушелей пшеницы";
        } else {
            std::cout << "Крысы не тронули запасы пшеницы";
        }
        std::cout << ", оставив " << wheal_bushels << " бушеля в амбарах;\n";

        std::cout << "\tГород сейчас занимает " << acres_of_land << " акров;\n";

        std::cout << "\t1 акр земли стоит сейчас " << acre_price << " бушель.\n";

        std::cout << "Что пожелаешь, повелитель? (Вы можете написать STOP в любой момент, чтобы остановить игру)\n";

        // Getting user input until he makes valid choice
        for (;;) {
            auto answer = get_answer_from_user("Сколько акров земли повелеваешь купить? ");
            if (answer.has_value()) {
                acres_to_buy = answer.value();
            } else {
                std::cout << BYE_BYE_MESSAGE << std::endl;
                return 0;
            }

            if (acres_to_buy == 0) {
                answer = get_answer_from_user("Сколько акров земли повелеваешь продать? ");
                if (answer.has_value()) {
                    acres_to_sell = answer.value();
                } else {
                    std::cout << BYE_BYE_MESSAGE << std::endl;
                    return 0;
                }
            } else {
                acres_to_sell = 0;
            }

            answer = get_answer_from_user("Сколько бушелей пшеницы повелеваешь съесть? ");
            if (answer.has_value()) {
                bushels_to_eat = answer.value();
            } else {
                std::cout << BYE_BYE_MESSAGE << std::endl;
                return 0;
            }

            answer = get_answer_from_user("Сколько акров земли повелеваешь засеять? ");
            if (answer.has_value()) {
                acres_to_plant = answer.value();
            } else {
                std::cout << BYE_BYE_MESSAGE << std::endl;
                return 0;
            }

            int32_t tmp_bushels = wheal_bushels;
            tmp_bushels -= acres_to_buy * acre_price;
            tmp_bushels += acres_to_sell * acre_price;
            tmp_bushels -= bushels_to_eat;
            tmp_bushels -= (acres_to_plant / 2) + (acres_to_plant % 2);
            int32_t tmp_acres = acres_of_land + acres_to_buy - acres_to_sell;
            if (tmp_bushels >= 0 && acres_to_sell <= acres_of_land && tmp_acres >= acres_to_plant) {
                acres_of_land = tmp_acres;
                wheal_bushels = tmp_bushels;
                break;
            } else {
                std::cout << "О, повелитель, пощади нас! У нас только " << people_amount << " человек, " << wheal_bushels << " бушелей пшеницы и " << acres_of_land
                          << " акров земли!\n";
            }
        }

        bushels_harvested = std::min(acres_to_plant, people_amount * 10) * wheal_per_acre;
        wheal_bushels += bushels_harvested;

        bushels_eaten_by_rats = wheal_bushels * proportion_eaten_by_rats;
        wheal_bushels -= bushels_eaten_by_rats;

        int32_t amount_of_people_can_be_fed = bushels_to_eat / 20;
        if (people_amount > amount_of_people_can_be_fed) {
            people_died = people_amount - amount_of_people_can_be_fed;
        } else {
            people_died = 0;
        }
        P += (double)people_died / people_amount / 10.0;

        if ((double)people_died / (double)people_amount > 0.45) {
            std::cout << BAD_END_MESSAGE << std::endl;
            return 0;
        }

        people_arrived = std::clamp((int32_t)(people_died / 2.0 + (5 - wheal_per_acre) * wheal_bushels / 600. + 1), 0, 50);
        people_amount = people_amount - people_died + people_arrived;

        was_plague = random_bool(0.15);
        if (was_plague) {
            people_amount /= 2;
        }

        old_wheal_per_acre = wheal_per_acre;
        round += 1;
    }

    double L = (double)acres_of_land / people_amount;

    if (P > 0.33 && L < 7.0) {
        std::cout << BAD_END_MESSAGE << std::endl;
    } else if (P > 0.10 && L < 9.0) {
        std::cout << HARD_HAND_END_MESSAGE << std::endl;
    } else if (P > 0.03 && L < 10.0) {
        std::cout << PRETTY_GOOD_END << std::endl;
    } else {
        std::cout << BEST_END << std::endl;
    }

    if (std::filesystem::exists(SAVE_FILE_PATH)) {
        std::filesystem::remove(SAVE_FILE_PATH);
    }

    return 0;
}

std::optional<int32_t> read_integer(std::istream& stream) {
    int32_t value;

    if (stream >> value) {
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    stream.clear();
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return std::nullopt;
}

std::optional<int32_t> get_answer_from_user(const char* question) {
    for (;;) {
        std::cout << question;

        std::string input;
        std::getline(std::cin, input);
        input = to_lower_ru(input);
        if (input == "stop") {
            return {};
        }
        std::stringstream stream(input);

        auto user_input = read_integer(stream);
        if (user_input.has_value() && user_input.value() >= 0) {
            return user_input.value();
        }

        std::cout << "Смилуйся, повелитель! Мы не понимаем высшую речь\n";
    }
}

bool random_bool(double probability) {
    static std::knuth_b rand_engine;

    std::bernoulli_distribution dist(probability);
    return dist(rand_engine);
}

std::string to_lower_ru(const std::string& str) {
    std::locale loc("ru_RU.UTF-8");
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [&loc](unsigned char c) { return std::tolower(c, loc); });

    return result;
}
