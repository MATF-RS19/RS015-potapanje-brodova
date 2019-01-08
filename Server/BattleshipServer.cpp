//
// Created by Nikola on 8.1.19..
//

#include "BattleshipServer.h"

#include <iostream>

using namespace std;

string BattleshipServer::getOpenGames() {
    string response = "";
    auto games = gameManager.getOpenGames();


    for (auto game : games) {
        response += game.getId() + "\n";
    }
    return response;
}

string BattleshipServer::registerUser(string username) {
    try {
        return gameManager.registerUser(username);
    } catch (char const *e) {
        cerr << e << endl;
        return "error"; // TODO error formatting
    }
}

string BattleshipServer::createGame(string username, string secret) {
    try {
        if (!gameManager.checkAuth(username, secret))
            throw "auth error"; // TODO should probably be in GameManager
        return gameManager.createGame(gameManager.getUserByName(username));
    } catch (char const *e) {
        cerr << e << endl;
        return "error"; // TODO error formatting
    }
}

string BattleshipServer::joinGame(string username, string secret, string gameId) {
    try {
        if (!gameManager.checkAuth(username, secret))
            throw "auth error"; // TODO should probably be in GameManager
        gameManager.joinGame(gameManager.getUserByName(username), gameId);
        return "OK";
    } catch (char const *e) {
        cerr << e << endl;
        return "error"; // TODO error formatting
    }
}

BattleshipServer::BattleshipServer() {
    gameManager = GameManager();
}
