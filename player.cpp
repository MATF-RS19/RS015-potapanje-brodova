#include "player.h"

Player::Player()
{
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            board[i][j]=0;
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
    if(board[x][y] != 0){
        board[x][y]=3;
        return true;
    }
    board[x][y]=2;
    return false;
}
