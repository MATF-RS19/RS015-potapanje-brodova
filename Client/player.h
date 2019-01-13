#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include "cellboard.h"
#include "ServerCommunicator.h"
#include "../config.h"

class Player {
private:
    QString name;
    QString enemyName;
    QString secret;
    int boardx;
    int boardy;
    int boardxe;
    int boardye;
    ServerCommunicator interface;

public:
    Player();
    std::string gameID = "";
    int board[BOARD_SIZE][BOARD_SIZE];
    int enemyBoard[BOARD_SIZE][BOARD_SIZE];
    int shipsPlaced;
    int numOfSunk;
    int numOfEnemySunk;
    cellBoard* cellboard;
    cellBoard* enemyCellBoard;

    void initGame(string);
    void pollGameState();


    bool isHit(int,int); // todo delete
    bool hasLost();
    void setName(QString);
    QString getName();
    void takeTurn(int x, int y, QString player);
    QString getSecret();
    void setSecret(QString secret);
    void setBoardX(int);
    void setBoardY(int);
    int getBoardX();
    int getBoardY();
    void setBoardXE(int);
    void setBoardYE(int);
    int getBoardXE();
    int getBoardYE();

    QString getEnemyName();
    void setEnemyName(QString name);
    string WinnerStatus;
};

#endif // PLAYER_H
