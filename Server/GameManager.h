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

class GameManager {
private:
public:
    std::vector<User> users;
    std::vector<Game> games;

    bool registerUser(std::string name);
    bool createGame(User &creator);

    std::vector<Game> getOpenGames() const;
//    bool joinGame(User auth, std::string gameId);
//    bool playTurn(User auth, std::string gameId, int turn_x, int turn_y);
    std::array<std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE>, 2> getGameState(User auth, std::string gameId) const;
    const Game &getGameById(std::string) const;
    Game &getGameById(std::string);
    friend std::ostream &operator<<(std::ostream &os, const GameManager &manager);

    const std::vector<Game> &getGames() const;
};


#endif //SERVER_GAMEMANAGER_H
