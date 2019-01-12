//
// Created by Nikola on 6.1.19..
//

#include <iostream>
#include "Game.h"
#include "Helper.h"

using namespace std;

Game::Game(User *_creator, vector<int> coords) {
    creator = _creator;
    if (coords.size() != 2 * NUMBER_OF_SHIPS)
        throw "8 ship coordinates required";

    id = Helper::getRandomString(10);

    for (int i = 0; i < BOARD_SIZE; i++) {
        creatorBoard[i].fill(EMPTY);
        challengerBoard[i].fill(EMPTY);
    }

    for (int i = 0; i < NUMBER_OF_SHIPS; i++) {
        creatorBoard[coords[i * 2]][coords[i * 2 + 1]] = PLACED;
    }
}

bool Game::playTurn(User *auth, int x, int y) {
    if (state != PLAYING)
        return false;
    if (*auth == *creator) {
        if (turn != CREATOR) return false;
        if (challengerBoard[x][y] == TARGETED || challengerBoard[x][y] == DESTROYED) return false;
        if (challengerBoard[x][y] == EMPTY) challengerBoard[x][y] = TARGETED;
        if (challengerBoard[x][y] == PLACED) {
            challengerBoard[x][y] = DESTROYED;
            checkState();
        }
        turn = CHALLENGER;
        return true;
    } else if (*auth == *challenger) {
        if (turn != CHALLENGER) return false;
        if (creatorBoard[x][y] == TARGETED || creatorBoard[x][y] == DESTROYED) return false;
        if (creatorBoard[x][y] == EMPTY) creatorBoard[x][y] = TARGETED;
        if (creatorBoard[x][y] == PLACED) {
            creatorBoard[x][y] = DESTROYED;
            checkState();
        }
        turn = CREATOR;
        return true;
    }
    return false;
}

void Game::checkState() {
    int destroyed = 0;
    for (auto row : creatorBoard)
        for (auto cell : row)
            if (cell == DESTROYED)
                destroyed++;
    if (destroyed == NUMBER_OF_SHIPS) {
        state = CHALLENGER_WON;
        return;
    }
    destroyed = 0;
    for (auto row : challengerBoard)
        for (auto cell : row)
            if (cell == DESTROYED)
                destroyed++;
    if (destroyed == NUMBER_OF_SHIPS) {
        state = CREATOR_WON;
        return;
    }
}

bool Game::setChallenger(User *_challenger, vector<int> coords) {
    if (coords.size() != 2 * NUMBER_OF_SHIPS)
        throw "8 ship coordinates required";

    for (int i = 0; i < BOARD_SIZE; i++) {
        challengerBoard[i].fill(EMPTY);
    }

    for (int i = 0; i < NUMBER_OF_SHIPS; i++) {
        challengerBoard[coords[i * 2]][coords[i * 2 + 1]] = PLACED;
    }

    challenger = _challenger;
    state = PLAYING;
    return true;
}

string Game::printBoard(std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> board) {
    string response;
    for (auto &row : board) {
        for (auto &cell : row)
            response += to_string(cell) + " ";
        response += "\n";
    }
    return response;
}

std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> Game::getCreatorBoard() const {
    return creatorBoard;
}

std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> Game::getChallengerBoard() const {
    return challengerBoard;
}

std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE>
Game::cleanOpponentBoard(std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> opponent_board) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (opponent_board[i][j] == PLACED)
                opponent_board[i][j] = EMPTY;
    return opponent_board;
}

const std::string &Game::getId() const {
    return id;
}

User *Game::getCreator() const {
    return creator;
}

User *Game::getChallenger() const {
    return challenger;
}

game_state Game::getState() const {
    return state;
}

game_turn Game::getTurn() const {
    return turn;
}
