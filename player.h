#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include <string>
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
    void takeTurn(Player* p,int x, int y, QString player);
    QString getSecret();
    void setSecret(QString secret);
    cellBoard* cellboard;
    int shipsPlaced;
    void setBoardX(int);
    void setBoardY(int);
    int getBoardX();
    int getBoardY();


private:
    QString name;
    QString secret;
    int boardx;
    int boardy;
};

#endif // PLAYER_H
