//
// Created by Nikola on 8.1.19..
//

#ifndef SERVER_BATTLESHIPSERVER_H
#define SERVER_BATTLESHIPSERVER_H

#include <string>
#include "GameManager.h"
#include "cpprest/http_listener.h"

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class BattleshipServer {
public:
    BattleshipServer();
    void handleRequest(http_request);
    string registerUser(string username);
    string createGame(string username, string secret, string ships);
    string joinGame(string username, string secret, string gameId, string ships);
    string getOpenGames();
    string getGameState(string username, string secret, string gameId);

    virtual ~BattleshipServer();

private:
    GameManager gameManager;
    http_listener listener;
};


#endif //SERVER_BATTLESHIPSERVER_H
