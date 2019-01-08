//
// Created by Nikola on 8.1.19..
//

#ifndef SERVER_BATTLESHIPSERVER_H
#define SERVER_BATTLESHIPSERVER_H

#include <string>
#include "GameManager.h"

using namespace std;

class BattleshipServer {
public:
    BattleshipServer();
    string registerUser(string username);
    string createGame(string username, string secret);
    string joinGame(string username, string secret, string gameId);
    string getOpenGames();

private:
    GameManager gameManager;
};


#endif //SERVER_BATTLESHIPSERVER_H
