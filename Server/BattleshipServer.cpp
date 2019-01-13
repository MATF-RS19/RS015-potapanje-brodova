//
// Created by Nikola on 8.1.19..
//

#include "BattleshipServer.h"

#include <iostream>
#include "cpprest/http_listener.h"
#include "../config.h"

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

string BattleshipServer::getOpenGames() {
    string response;
    auto games = gameManager.getOpenGames();


    for (auto &game : games) {
        response += game->getId() + " " + game->getCreator()->getName() + "\n";
    }
    return response;
}

string BattleshipServer::registerUser(string username) {
    return gameManager.registerUser(username);
}

string BattleshipServer::createGame(string username, string secret, string ships) {
    return gameManager.createGame(username, secret, ships);
}

string BattleshipServer::joinGame(string username, string secret, string gameId, string ships) {
    gameManager.joinGame(username, secret, gameId, ships);
    return "OK";
}

string BattleshipServer::getGameState(string username, string secret, string gameId) {
    return gameManager.getGameState(username, secret, gameId);
}

string BattleshipServer::playTurn(string username, string secret, string gameId, string x, string y) {
    return gameManager.playTurn(username, secret, gameId, stoi(x), stoi(y));
}

string BattleshipServer::unregisterUser(string username, string secret) {
    gameManager.unregisterUser(username, secret);
    return "OK";
}

void BattleshipServer::handleRequest(http_request request) {
    string path = request.request_uri().path();
    cout << path << endl;

    auto params = uri::split_query(request.request_uri().query());

    try {
        if (path == "/register") {
            // TODO check if params exist
            string username = params.find("username")->second;
            request.reply(status_codes::OK, registerUser(username));
        } else if (path == "/create") {
            // TODO check if params exist
            string username = params.find("username")->second;
            string secret = params.find("secret")->second;
            string ships = params.find("ships")->second;
            request.reply(status_codes::OK, createGame(username, secret, ships));
        } else if (path == "/join") {
            // TODO check if params exist
            string username = params.find("username")->second;
            string secret = params.find("secret")->second;
            string gameId = params.find("gameid")->second;
            string ships = params.find("ships")->second;
            request.reply(status_codes::OK, joinGame(username, secret, gameId, ships));
        } else if (path == "/game") {
            // TODO check if params exist
            string username = params.find("username")->second;
            string secret = params.find("secret")->second;
            string gameId = params.find("gameid")->second;
            request.reply(status_codes::OK, getGameState(username, secret, gameId));
        } else if (path == "/play") {
            // TODO check if params exist
            string username = params.find("username")->second;
            string secret = params.find("secret")->second;
            string gameId = params.find("gameid")->second;
            string x = params.find("x")->second;
            string y = params.find("y")->second;
            request.reply(status_codes::OK, playTurn(username, secret, gameId, x, y));
        } else if (path == "/games") {
            request.reply(status_codes::OK, getOpenGames());
        } else if (path == "/unregister") {
            // TODO check if params exist
            string username = params.find("username")->second;
            string secret = params.find("secret")->second;
            request.reply(status_codes::OK, unregisterUser(username, secret));
        } else {
            request.reply(status_codes::OK, "hello");
        }
    } catch (char const *e) {
        request.reply(status_codes::BadRequest, e);
    }
}

BattleshipServer::BattleshipServer() {
    gameManager = GameManager();

    cout << "Web Server starting..." << endl;

    listener = http_listener(string("http://0.0.0.0:") + SERVER_PORT);
    listener.support(methods::GET, [this](http_request request) {
        this->handleRequest(request);
    });

    listener.open()
            .then([]() { cout << "Web Server listening..." << endl; })
            .wait();
}

BattleshipServer::~BattleshipServer() {
    listener.close();
}
