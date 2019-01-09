#include <iostream>
#include "GameManager.h"
#include "BattleshipServer.h"

using namespace std;

int testGameManager() {
    GameManager gm = GameManager();

    string secret1 = gm.registerUser("Korisnik 1");
    string secret2 = gm.registerUser("Korisnik 2");

    string gameId = gm.createGame("Korisnik 1", secret1, "0,0,1,1,2,2,3,4,4,4,5,5,6,6,7,7");
    gm.joinGame("Korisnik 2", secret2, gameId, "0,0,1,1,2,2,3,4,4,4,5,5,6,6,7,7");

    cout << Game::printBoard(gm.getGames().at(0).getCreatorBoard()) << endl;
//    cout << Game::printBoard(gm.getGames().at(0).getOpponentBoard()) << endl;

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