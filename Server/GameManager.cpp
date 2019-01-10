//
// Created by Nikola on 6.1.19..
//

#include "GameManager.h"
#include "Helper.h"

#include <iostream>
#include <string>
#include <sstream>

bool GameManager::checkAuth(User *auth) {
    return checkAuth(auth->getName(), auth->getSecret());
}

bool GameManager::checkAuth(string username, string secret) const {
    auto user = find_if(users.begin(), users.end(),
                        [username](const User *user) { return user->getName() == username; });
    if (user == users.end()) return false;
    return (*user)->getName() == username && (*user)->getSecret() == secret;
}

string GameManager::registerUser(std::string name) {
    if (std::find_if(users.begin(), users.end(), [name](const User *user) {
        return user->getName() == name;
    }) != users.end())
        throw "Username taken";
    auto user = new User(name);
    users.emplace_back(user);
    return user->getSecret();
}

string GameManager::createGame(string username, string secret, string ships) {
    auto coords = Helper::parseShipCoords(ships);
    if (!checkAuth(username, secret))
        throw "Auth error";
    // TODO should prevent user from creating multiple games?
    auto game = Game(getUserByName(username), coords);
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
    auto user = find_if(users.begin(), users.end(), [name](const User *_user) -> bool {
        return _user->getName() == name;
    });
    if (user == users.end())
        throw "Game with given ID not found";
    return *user;
}

User *GameManager::getUserByName(std::string name) {
    auto user = find_if(users.begin(), users.end(), [name](const User *_user) -> bool {
        return _user->getName() == name;
    });
    if (user == users.end())
        throw "Game with given ID not found";
    return *user;
}

string GameManager::getGameState(string username, string secret, std::string gameId) const {
    if (!checkAuth(username, secret))
        throw "Auth error";
    const Game *game = getGameById(gameId);
    const User *user = getUserByName(username);
    if (*user != *(game->getCreator()) && *user != *(game->getChallenger()))
        throw "Not authorized to see game";

    string response;
    if (*user == *(game->getCreator())) {
        response += Game::printBoard(game->getCreatorBoard());
        response += "\n";
        response += Game::printBoard(Game::cleanOpponentBoard(game->getChallengerBoard()));
        response += "\n";
        response += ((game->getTurn() == CREATOR) ? "Your turn" : "Waiting turn");
    } else {
        response += Game::printBoard(game->getChallengerBoard());
        response += "\n";
        response += Game::printBoard(Game::cleanOpponentBoard(game->getCreatorBoard()));
        response += "\n";
        response += ((game->getTurn() == CHALLENGER) ? "Your turn" : "Waiting turn");
    }

    response += "\n";
    response += "Game state: ";
    response += game->getState() == PLAYING ? "Game ongoing" : "Game finished";

    return response;
}

std::ostream &operator<<(std::ostream &os, const GameManager &manager) {
    os << "Game Manager with " << manager.users.size() << " user/s and "
       << manager.games.size() << " game/s (" << manager.getOpenGames().size() << " open)";
    return os;
}

bool GameManager::joinGame(string username, string secret, string gameId, string ships) {
    if (!checkAuth(username, secret))
        throw "Auth error";
    Game *game = getGameById(gameId);
    auto coords = Helper::parseShipCoords(ships);
    return game->setChallenger(getUserByName(username), coords);
}

bool GameManager::playTurn(string username, string secret, string gameId, int turn_x, int turn_y) {
    if (!checkAuth(username, secret))
        throw "Auth error";
    Game *game = getGameById(gameId);
    User *user = getUserByName(username);
    return game->playTurn(user, turn_x, turn_y);
}