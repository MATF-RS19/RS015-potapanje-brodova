#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include <cellboard.h>

class Player
{
public:
    Player();
    bool isHit(int,int);
    void setName(QString);
    QString getName();
    bool hasLost();
    int board[10][10];
    int enemyBoard[10][10];
    void takeTurn(int x, int y, QString player);
    QString getSecret();
    void setSecret(QString secret);
    cellBoard* cellboard;
    cellBoard* enemyCellBoard;
    int shipsPlaced;
    void setBoardX(int);
    void setBoardY(int);
    int getBoardX();
    int getBoardY();
    void setBoardXE(int);
    void setBoardYE(int);
    int getBoardXE();
    int getBoardYE();
    int numOfSunk;
    int numOfEnemySunk;


    std::string gameID = "";

    QString  getEnemyName();
    void setEnemyName(QString name);


private:
    QString name;
    QString enemyName;
    QString secret;
    int boardx;
    int boardy;
    int boardxe;
    int boardye;
};

#endif // PLAYER_H
