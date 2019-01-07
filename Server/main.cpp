#include <iostream>
#include "GameManager.h"

int main() {
    GameManager gm = GameManager();

    assert(gm.registerUser("Korisnik 1"));
    assert(gm.registerUser("Korisnik 2"));
    assert(!gm.registerUser("Korisnik 2"));

    gm.createGame(gm.users.at(0));

    Game::printBoard(gm.getGames().at(0).getBoard());
    Game::printBoard(gm.getGames().at(0).getOpponentBoard());

    std::cout << gm << std::endl;
    return 0;
}