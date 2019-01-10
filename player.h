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
    int shipesPlaced=0;
    QString getSecret();
    void setSecret(QString secret);
    cellBoard* cellboard;

private:
    QString name;
    QString secret;
};

#endif // PLAYER_H
