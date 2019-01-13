//
// Created by Nikola on 6.1.19..
//

#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <string>
#include <array>
#include <vector>

#include "User.h"
#include "../config.h"

using namespace std;

enum game_state {
    OPEN,
    PLAYING,
    CREATOR_WON,
    CHALLENGER_WON,
};
enum game_turn {
    CREATOR,
    CHALLENGER
};
enum cell {
    EMPTY,
    PLACED,
    TARGETED,
    DESTROYED
};

class Game {
private:
    std::string id;
    User *creator;
    User *challenger;
    time_t lastActive;
    game_state state = OPEN;
    game_turn turn = CHALLENGER;
    std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> creatorBoard;
    std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> challengerBoard;

public:
    Game(User *creator, vector<int>);
    string playTurn(User *auth, int x, int y);
    std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> getCreatorBoard();
    std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> getChallengerBoard();
    bool setChallenger(User *challenger, vector<int>);
    void checkState();

    void updateLastActive();
    bool timedOut() const;

    static std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> cleanOpponentBoard(std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE>);
    static string printBoard(std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> board);

    const std::string &getId() const;
    User *getCreator() const;
    User *getChallenger() const;
    game_state getState() const;
    game_turn getTurn() const;
};


#endif //SERVER_GAME_H
