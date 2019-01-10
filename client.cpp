#include <iostream>

#include "ServerCommunicator.h"

using namespace std;

int main() {
    ServerCommunicator interface;
    try {
        cout << "Registering user" << endl;
        string secret1 = interface.registerUser("nikola");
        cout << "Secret: " << secret1 << endl;

        cout << "Creating game" << endl;
        string gameId = interface.createGame("nikola", secret1, "0,0,1,1,2,2,3,4,4,4,5,5,6,6,7,7");
        cout << "Game ID: " << gameId << endl;

        cout << "Registering user 2" << endl;
        string secret2 = interface.registerUser("stefan");
        cout << "Secret: " << secret1 << endl;

        cout << "Joining game" << endl;
        string resp = interface.joinGame("stefan", secret2, gameId, "0,0,1,1,2,2,3,4,4,4,5,5,6,6,7,7");
        cout << resp << endl;

        cout << "Polling game state for challenger" << endl;
        resp = interface.getGameState("stefan", secret2, gameId);
        cout << resp << endl;

        cout << "Playing 3 5" << endl;
        resp = interface.playTurn("stefan", secret2, gameId, 3, 5);
        cout << resp << endl;

        cout << "Polling game state for challenger" << endl;
        resp = interface.getGameState("stefan", secret2, gameId);
        cout << resp << endl;

        cout << "Polling game state for creator" << endl;
        resp = interface.getGameState("nikola", secret1, gameId);
        cout << resp << endl;

        cout << "end" << endl;
    } catch (string &e) {
        cerr << e;
    }


    return 0;
}