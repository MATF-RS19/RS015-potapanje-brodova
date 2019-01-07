//
// Created by Nikola on 6.1.19..
//

#include "GameManager.h"

#include <iostream>

bool GameManager::registerUser(std::string name) {
    if (std::find(users.begin(), users.end(), name) != users.end())
        return false;
    users.emplace_back(User(name));
    return true;
}

bool GameManager::createGame(User &creator) {
    // TODO should prevent user from creating multiple games?
    games.emplace_back(Game(creator));
    return true;
}

const std::vector<Game> &GameManager::getGames() const {
    return games;
}

std::vector<Game> GameManager::getOpenGames() const {
    std::vector<Game> open_games {};
    for (const Game &game : games)
        if (game.getState() == OPEN)
            open_games.emplace_back(game);
    return open_games;
}

const Game &GameManager::getGameById(std::string id) const {
    auto game = find_if(games.begin(), games.end(), [id](const Game &_game) -> bool {
        return _game.getId() == id;
    });
    if (game == games.end())
        throw "Game with given ID not found";
    return *game;
}

Game &GameManager::getGameById(std::string gameId) {
    return const_cast<Game &>(static_cast<const Game &>((*this).getGameById(gameId)));
}

std::array<std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE>, 2> GameManager::getGameState(User auth, std::string gameId) const {
    const Game game = getGameById(gameId);
    if (auth != game.getCreator() && auth != game.getChallenger())
        throw "Auth error";
    return std::array<std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE>, 2> { game.getBoard(), game.getOpponentBoard() };
}

std::ostream &operator<<(std::ostream &os, const GameManager &manager) {
    os << "Game Manager with " << manager.users.size() << " user/s and "
       << manager.games.size() << " game/s (" << manager.getOpenGames().size() << " open)";
    return os;
}
