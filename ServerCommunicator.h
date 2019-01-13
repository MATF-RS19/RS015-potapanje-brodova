//
// Created by Nikola Vukovic on 2019-01-09.
//

#ifndef SERVER_SERVERCOMMUNICATOR_H
#define SERVER_SERVERCOMMUNICATOR_H

#include <string>
#include <vector>
#include <utility>
#include <cpprest/http_client.h>

using namespace std;
using namespace web::http::client;

class ServerCommunicator {
private:
    http_client client;
public:
    ServerCommunicator();
    string registerUser(string username);
    string createGame(string username, string secret, string ships);
    string joinGame(string username, string secret, string ships, string gameId);
    string getGameState(string username, string secret, string gameId);
    string playTurn(string username, string secret, string gameId, int turn_x, int turn_y);
    void unregister(string username, string secret);
    vector<pair<string, string>> getOpenGames();
};


#endif //SERVER_SERVERCOMMUNICATOR_H
