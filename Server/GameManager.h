//
// Created by Nikola on 6.1.19..
//

#ifndef SERVER_GAMEMANAGER_H
#define SERVER_GAMEMANAGER_H

#include <vector>
#include <string>
#include <ostream>

#include "User.h"
#include "Game.h"

using namespace std;

class GameManager {
private:
public:
    vector<User> users;
    vector<Game> games;

    string registerUser(string name);
    string createGame(User *creator);

    vector<Game> getOpenGames() const;
    bool joinGame(User *auth, string gameId);
//    bool playTurn(User auth, string gameId, int turn_x, int turn_y);
    array<array<array<cell, BOARD_SIZE>, BOARD_SIZE>, 2> getGameState(User auth, string gameId) const;
    const Game *getGameById(string) const;
    Game *getGameById(string);
    const User *getUserByName(std::string name) const;
    User *getUserByName(std::string name);
    friend ostream &operator<<(ostream &os, const GameManager &manager);
    const vector<Game> &getGames() const;
    bool checkAuth(string username, string secret);
    bool checkAuth(User &auth);
};


#endif //SERVER_GAMEMANAGER_H
