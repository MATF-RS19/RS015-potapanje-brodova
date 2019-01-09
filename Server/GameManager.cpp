//
// Created by Nikola on 6.1.19..
//

#include "GameManager.h"

#include <iostream>

string GameManager::registerUser(std::string name) {
    if (std::find_if(users.begin(), users.end(), [name](const User &user) {
        return user.getName() == name;
    }) != users.end())
        throw "Username taken";
    auto user = User(name);
    users.emplace_back(user);
    return user.getSecret();
}

string GameManager::createGame(string username, string secret) {
    if (!checkAuth(username, secret))
        throw "auth error";
    // TODO should prevent user from creating multiple games?
    auto game = Game(getUserByName(username));
    games.emplace_back(game);
    return game.getId();
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

const Game *GameManager::getGameById(std::string id) const {
    auto game = find_if(games.begin(), games.end(), [id](const Game &_game) -> bool {
        return _game.getId() == id;
    });
    if (game == games.end())
        throw "Game with given ID not found";
    return &*game;
}

Game *GameManager::getGameById(std::string gameId) {
    auto game = find_if(games.begin(), games.end(), [gameId](const Game &_game) -> bool {
        return _game.getId() == gameId;
    });
    if (game == games.end())
        throw "Game with given ID not found";
    return &*game;
}

const User *GameManager::getUserByName(std::string name) const {
    auto user = find_if(users.begin(), users.end(), [name](const User &_user) -> bool {
        return _user.getName() == name;
    });
    if (user == users.end())
        throw "Game with given ID not found";
    return &*user;
}

User *GameManager::getUserByName(std::string name) {
    auto user = find_if(users.begin(), users.end(), [name](const User &_user) -> bool {
        return _user.getName() == name;
    });
    if (user == users.end())
        throw "Game with given ID not found";
    return &*user;
}

std::array<std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE>, 2>
GameManager::getGameState(User auth, std::string gameId) const {
    const Game *game = getGameById(gameId);
    if (auth != *(game->getCreator()) && auth != *(game->getChallenger()))
        throw "Auth error";
    return std::array<std::array<std::array<cell, BOARD_SIZE>, BOARD_SIZE>, 2> {game->getBoard(),
                                                                                game->getOpponentBoard()};
}

std::ostream &operator<<(std::ostream &os, const GameManager &manager) {
    os << "Game Manager with " << manager.users.size() << " user/s and "
       << manager.games.size() << " game/s (" << manager.getOpenGames().size() << " open)";
    return os;
}

bool GameManager::checkAuth(User *auth) {
    return checkAuth(auth->getName(), auth->getSecret());
}

bool GameManager::checkAuth(string username, string secret) {
    auto user = find_if(users.begin(), users.end(),
                        [username](const User &user) { return user.getName() == username; });
    if (user == users.end()) return false;
    return user->getName() == username && user->getSecret() == secret;
}

bool GameManager::joinGame(string username, string secret, string gameId) {
    if (!checkAuth(username, secret))
        throw "auth error";
    Game *game = getGameById(gameId);
    return game->setChallenger(getUserByName(username));
}