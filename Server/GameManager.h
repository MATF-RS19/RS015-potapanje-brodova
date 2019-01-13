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
    vector<User*> users;
    vector<Game*> games;

    string registerUser(string username);
    void unregisterUser(string username, string secret);
    string createGame(string username, string secret, string ships);

    vector<Game*> getOpenGames();
    bool joinGame(string username, string secret, string gameId, string ships);
    bool playTurn(string username, string secret, string gameId, int turn_x, int turn_y);
    string getGameState(string username, string secret, string gameId);
    const Game *getGameById(string) const;
    Game *getGameById(string);
    const User *getUserByName(std::string name) const;
    User *getUserByName(std::string name);
    friend ostream &operator<<(ostream &os, const GameManager &manager);
    const vector<Game*> &getGames() const;
    bool checkAuth(string username, string secret) const;
    bool checkAuth(User *auth);
};


#endif //SERVER_GAMEMANAGER_H
