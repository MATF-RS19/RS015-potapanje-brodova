//
// Created by Nikola on 8.1.19..
//

#ifndef SERVER_HELPER_H
#define SERVER_HELPER_H

#include <string>
#include <vector>

using namespace std;

class Helper {
public:
    static string getRandomString(int length);
    static vector<int> parseShipCoords(string ships);
};


#endif //SERVER_HELPER_H
