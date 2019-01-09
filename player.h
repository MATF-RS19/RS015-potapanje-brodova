#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>

class Player
{
public:
    Player();
    bool isHit(int,int);
    void setName(QString);
    QString getName();
    bool hasLost();
    int board[10][10];

private:
    QString name;
};

#endif // PLAYER_H
