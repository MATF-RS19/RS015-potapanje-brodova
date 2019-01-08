#include <iostream>
#include "GameManager.h"
#include "BattleshipServer.h"

using namespace std;

int testGameManager() {
    GameManager gm = GameManager();

    gm.registerUser("Korisnik 1");
    gm.registerUser("Korisnik 2");

    gm.createGame(&gm.users.at(0));

    Game::printBoard(gm.getGames().at(0).getBoard());
    Game::printBoard(gm.getGames().at(0).getOpponentBoard());

    cout << gm << endl << endl;
    return 0;
}

int main() {
    cout << unitbuf;

    BattleshipServer server = BattleshipServer();

    cout << "Registering user Nikola: " << endl;
    string secret1 = server.registerUser("Nikola");
    cout << secret1 << endl << endl;
    cout << "Registering user Matija: " << endl;
    string secret2 = server.registerUser("Matija");
    cout << secret2 << endl << endl;
    cout << "Registering user Stefan: " << endl;
    string secret3 = server.registerUser("Stefan");
    cout << secret3 << endl << endl;
    cout << "Registering user Stefan again: " << endl << server.registerUser("Stefan") << endl << endl;

    cout << "New game id: " << endl;
    string gameId1 = server.createGame("Nikola", secret1);
    cout << gameId1 << endl << endl;
    cout << "New game id: " << server.createGame("Matija", "test") << endl << endl;

    cout << "Open games: " << endl << server.getOpenGames() << endl;

    cout << "Joining game: " << endl << server.joinGame("Stefan", secret3, "game test id") << endl << endl;
    cout << "Joining game: " << endl << server.joinGame("Stefan", secret3, gameId1) << endl << endl;

    cout << "Open games: " << endl << server.getOpenGames() << endl;


    return 0;
}