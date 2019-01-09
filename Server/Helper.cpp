//
// Created by Nikola on 8.1.19..
//

#include "Helper.h"

#include <random>
#include <string>
#include <sstream>

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

vector<int> Helper::parseShipCoords(string ships) {
    stringstream stream(ships);
    string segment;
    vector<int> coords;

    while(std::getline(stream, segment, ','))
    {
        coords.emplace_back(stoi(segment));
    }

    return coords;
}