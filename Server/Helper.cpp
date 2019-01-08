//
// Created by Nikola on 8.1.19..
//

#include "Helper.h"

#include <random>

string Helper::getRandomString(int length) {
    string s = "";
    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<> dist(0, 25);
    for (int i = 0; i < length; i++) {
        auto rand = dist(engine);
        s += letters[rand];
    }
    return s;
}