#include <iostream>
#include "GameManager.h"
#include "BattleshipServer.h"

using namespace std;

int testGameManager() {
    GameManager gm = GameManager();

    string secret1 = gm.registerUser("Korisnik 1");
    gm.registerUser("Korisnik 2");

    gm.createGame("Korisnik 1", secret1);

    Game::printBoard(gm.getGames().at(0).getBoard());
    Game::printBoard(gm.getGames().at(0).getOpponentBoard());

    cout << gm << endl << endl;
    return 0;
}

int main() {
    cout << unitbuf;

    BattleshipServer server;

    string line;
    getline(cin, line);

    return 0;
}