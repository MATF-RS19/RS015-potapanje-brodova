//
// Created by Nikola on 6.1.19..
//

#include "GameManager.h"
#include "Helper.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

bool GameManager::checkAuth(User *auth) {
    return checkAuth(auth->getName(), auth->getSecret());
}

bool GameManager::checkAuth(string username, string secret) const {
    auto user = find_if(users.begin(), users.end(),
                        [username](const User *user) { return user->getName() == username; });
    if (user == users.end()) return false;
    return (*user)->getName() == username && (*user)->getSecret() == secret;
}

string GameManager::registerUser(std::string username) {
    auto usernameConflict = std::find_if(users.begin(), users.end(), [username](const User *user) {
        return user->getName() == username;
    });
    if (usernameConflict != users.end()) {
        if ((*usernameConflict)->timedOut())
            unregisterUser(username, (*usernameConflict)->getSecret());
        else
            throw "Username taken";
    }
    auto user = new User(username);
    users.emplace_back(user);
    return user->getSecret();
}

void GameManager::unregisterUser(string username, string secret) {
    if (!checkAuth(username, secret))
        throw "Auth error";
    games.erase(remove_if(games.begin(), games.end(), [username](const Game *game) {
        return game->getCreator()->getName() == username || game->getChallenger()->getName() == username;
    }), games.end());
    users.erase(remove_if(users.begin(), users.end(), [username](const User *user) {
        return user->getName() == username;
    }), users.end());
}

string GameManager::createGame(string username, string secret, string ships) {
    if (!checkAuth(username, secret))
        throw "Auth error";
    // TODO should prevent user from creating multiple games?
    User *user = getUserByName(username);
    user->updateLastActive();
    auto coords = Helper::parseShipCoords(ships);
    Game* game = new Game(user, coords);
    games.emplace_back(game);
    return game->getId();
}

const std::vector<Game*> &GameManager::getGames() const {
    return games;
}

std::vector<Game*> GameManager::getOpenGames() {
    std::vector<Game*> open_games {};
    games.erase(remove_if(games.begin(), games.end(), [](const Game *game) { return game->timedOut(); }), games.end());
    for (Game *game : games)
        if (game->getState() == OPEN)
            open_games.emplace_back(game);
    return open_games;
}

const Game *GameManager::getGameById(std::string gameId) const {
    auto game = find_if(games.begin(), games.end(), [gameId](const Game *_game) -> bool {
        return _game->getId() == gameId;
    });
    if (game == games.end())
        throw "Game with given ID not found";
    return *game;
}

Game *GameManager::getGameById(std::string gameId) {
    auto game = find_if(games.begin(), games.end(), [gameId](const Game *_game) -> bool {
        return _game->getId() == gameId;
    });
    if (game == games.end())
        throw "Game with given ID not found";
    return *game;
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

string GameManager::getGameState(string username, string secret, std::string gameId) {
    if (!checkAuth(username, secret))
        throw "Auth error";
    Game *game = getGameById(gameId);
    User *user = getUserByName(username);
    if (*user != *(game->getCreator()) && *user != *(game->getChallenger()))
        throw "Not authorized to see game";

    bool isCreator = *user == *(game->getCreator());

    string response;

    if (isCreator) {
        response += Game::printBoard(game->getCreatorBoard());
        response += "\n";
        response += Game::printBoard(Game::cleanOpponentBoard(game->getChallengerBoard()));
        response += "\n";
        response += game->getState() == OPEN
                ? "enemy"
                : ((game->getTurn() == CREATOR) ? game->getCreator() : game->getChallenger())->getName();
        game->getCreator()->updateLastActive();
    } else {
        response += Game::printBoard(game->getChallengerBoard());
        response += "\n";
        response += Game::printBoard(Game::cleanOpponentBoard(game->getCreatorBoard()));
        response += "\n";
        response += ((game->getTurn() == CHALLENGER) ? game->getChallenger() : game->getCreator())->getName();
        game->getChallenger()->updateLastActive();
    }

    response += "\n";
    if (game->getState() == OPEN)
        response += "open";
    else if (game->getState() == PLAYING)
        response += "playing";
    else if (game->getState() == CREATOR_WON)
        response += isCreator ? "won" : "lost";
    else if (game->getState() == CHALLENGER_WON)
        response += isCreator ? "lost" : "won";

    response += "\n";
    response += (game->getState() == OPEN)
            ? "\n"
            : (isCreator ? game->getChallenger() : game->getCreator())->getName();

    return response;
}

std::ostream &operator<<(std::ostream &os, const GameManager &manager) {
    os << "Game Manager with " << manager.users.size() << " user/s and "
       << manager.games.size() << " game/s";
    return os;
}

bool GameManager::joinGame(string username, string secret, string gameId, string ships) {
    if (!checkAuth(username, secret))
        throw "Auth error";
    Game *game = getGameById(gameId);
    auto coords = Helper::parseShipCoords(ships);
    User *user = getUserByName(username);
    user->updateLastActive();
    return game->setChallenger(user, coords);
}

bool GameManager::playTurn(string username, string secret, string gameId, int turn_x, int turn_y) {
    if (!checkAuth(username, secret))
        throw "Auth error";
    Game *game = getGameById(gameId);
    User *user = getUserByName(username);
    user->updateLastActive();
    return game->playTurn(user, turn_x, turn_y);
}