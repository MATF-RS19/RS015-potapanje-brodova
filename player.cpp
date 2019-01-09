#include "player.h"

Player::Player()
{
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            this->board[i][j]=0;
        }
    }
}

void Player::setName(QString name){
    this->name=name;
}

QString Player::getName(){
    return name;
}

bool Player::isHit(int x,int y){
    if(this->board[x][y] == 1){
        this->board[x][y]=3;
        return true;
    }
    this->board[x][y]=2;
    return false;
}
