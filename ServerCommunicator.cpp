//
// Created by Nikola Vukovic on 2019-01-09.
//

#include "ServerCommunicator.h"

#include <cpprest/http_client.h>
#include "config.h"

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

ServerCommunicator::ServerCommunicator() : client(string("http://") + SERVER_ADDRESS + ":" + SERVER_PORT) {}

string ServerCommunicator::registerUser(string username) {
    int statusCode = 200;
    uri_builder builder("/register");
    builder.append_query("username", username);
    pplx::task<string> requestTask = client.request(methods::GET, builder.to_string())
        .then([&statusCode](http_response response) mutable {
            statusCode = response.status_code();
            return response.extract_string();
        })
        .then([=](string body) {
            return body;
        });
    requestTask.wait();
    if (statusCode == 200)
        return requestTask.get();
    throw requestTask.get();
}

string ServerCommunicator::createGame(string username, string secret, string ships) {
    int statusCode = 200;
    uri_builder builder("/create");
    builder.append_query("username", username);
    builder.append_query("secret", secret);
    builder.append_query("ships", ships);
    pplx::task<string> requestTask = client.request(methods::GET, builder.to_string())
        .then([&statusCode](http_response response) mutable {
            statusCode = response.status_code();
            return response.extract_string();
        })
        .then([=](string body) {
            return body;
        });
    requestTask.wait();
    if (statusCode == 200)
        return requestTask.get();
    throw requestTask.get();
}

string ServerCommunicator::joinGame(string username, string secret, string gameId, string ships) {
    int statusCode = 200;
    uri_builder builder("/join");
    builder.append_query("username", username);
    builder.append_query("secret", secret);
    builder.append_query("ships", ships);
    builder.append_query("gameid", gameId);
    pplx::task<string> requestTask = client.request(methods::GET, builder.to_string())
        .then([&statusCode](http_response response) mutable {
            statusCode = response.status_code();
            return response.extract_string();
        })
        .then([=](string body) {
            return body;
        });
    requestTask.wait();
    if (statusCode == 200)
        return requestTask.get();
    throw requestTask.get();
}

string ServerCommunicator::getGameState(string username, string secret, string gameId) {
    int statusCode = 200;
    uri_builder builder("/game");
    builder.append_query("username", username);
    builder.append_query("secret", secret);
    builder.append_query("gameid", gameId);
    pplx::task<string> requestTask = client.request(methods::GET, builder.to_string())
        .then([&statusCode](http_response response) mutable {
            statusCode = response.status_code();
            return response.extract_string();
        })
        .then([=](string body) {
            return body;
        });
    requestTask.wait();
    if (statusCode == 200)
        return requestTask.get();
    throw requestTask.get();
}

string ServerCommunicator::playTurn(string username, string secret, string gameId, int turn_x, int turn_y) {
    int statusCode = 200;
    uri_builder builder("/play");
    builder.append_query("username", username);
    builder.append_query("secret", secret);
    builder.append_query("gameid", gameId);
    builder.append_query("x", turn_x);
    builder.append_query("y", turn_y);
    pplx::task<string> requestTask = client.request(methods::GET, builder.to_string())
        .then([&statusCode](http_response response) mutable {
            statusCode = response.status_code();
            return response.extract_string();
        })
        .then([=](string body) {
            return body;
        });
    requestTask.wait();
    if (statusCode == 200)
        return requestTask.get();
    throw requestTask.get();
}