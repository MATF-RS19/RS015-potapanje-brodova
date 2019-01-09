//
// Created by Nikola on 8.1.19..
//

#include "BattleshipServer.h"

#include <iostream>
#include "cpprest/http_listener.h"

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

string BattleshipServer::getOpenGames() {
    string response;
    auto games = gameManager.getOpenGames();


    for (auto &game : games) {
        response += game.getId() + "\n";
    }
    return response;
}

string BattleshipServer::registerUser(string username) {
    return gameManager.registerUser(username);
}

string BattleshipServer::createGame(string username, string secret) {
    return gameManager.createGame(username, secret);
}

string BattleshipServer::joinGame(string username, string secret, string gameId) {
    gameManager.joinGame(username, secret, gameId);
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
            request.reply(status_codes::OK, createGame(username, secret));
        } else if (path == "/join") {
            // TODO check if params exist
            string username = params.find("username")->second;
            string secret = params.find("secret")->second;
            string gameId = params.find("gameid")->second;
            request.reply(status_codes::OK, joinGame(username, secret, gameId));
        } else if (path == "/games") {
            request.reply(status_codes::OK, getOpenGames());
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

    listener = http_listener("http://localhost:8080");
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
