//
// Created by Nikola on 6.1.19..
//

#include <iostream>
#include "Game.h"
#include "Helper.h"

Game::Game(User *creator) : creator(creator), challenger(creator) {
    id = Helper::getRandomString(10);

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i].fill(EMPTY);
    }

    board[1][2] = PLACED;
    board[1][3] = TARGETED;
    board[1][4] = DESTROYED;
}

bool Game::playTurn(User *auth, int x, int y) {
    if (*auth != *creator) return false; // consider moving auth check to GameManager
    if (board[x][y] == TARGETED || board[x][y] == DESTROYED) return false;
    if (board[x][y] == EMPTY) board[x][y] = TARGETED;
    if (board[x][y] == PLACED) board[x][y] = DESTROYED;
    // TODO check if game finished
    return true;
}

bool Game::setChallenger(User *_challenger) {
    challenger = _challenger;
    state = PLAYING;
    return true;
}

void Game::printBoard(std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> board) {
    for (auto &row : board) {
        for (auto &cell : row)
            std::cout << cell << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> Game::getBoard() const {
    return board;
}

std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> Game::getOpponentBoard() const {
    std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE> opponent_board;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            opponent_board[i][j] = board[i][j] == PLACED ? EMPTY : board[i][j];
        }
    }
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
