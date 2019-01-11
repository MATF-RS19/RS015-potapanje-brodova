#include "player.h"
#include "battleshipgame.h"
#include "cellboard.h"
#include "config.h"
extern BattleshipGame* game;

Player::Player()
{
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            this->board[i][j]=0;
        }
    }
    cellboard = new cellBoard();
    shipsPlaced=0;
}

void Player::setName(QString name){
    this->name=name;
}

QString Player::getName(){
    return name;
}

void Player::setSecret(QString secret){
    this->secret = secret;
}

QString Player::getSecret(){
    return secret;
}

bool Player::isHit(int x,int y){
    if(this->board[x][y] == 1){
        this->board[x][y]=3;
        return true;
    }
    this->board[x][y]=2;
    return false;
}


void Player::takeTurn(Player* enemy,int x, int y,QString player){

    if(enemy->getName() != player){
        return;
    }

    if(enemy->board[x][y] ==2 || enemy->board[x][y] == 3){
        return;
    }

    std::cout << "polje" << x << " " << y << "gadja :" << game->getWhoseTurn().toStdString() << std::endl;

    QGraphicsPixmapItem* p = new QGraphicsPixmapItem();

    if(enemy->board[x][y]==1){
        std::cout << "pogodak" << std::endl;
        p->setPixmap(QPixmap(":/images/images/fire.png"));
        p->setPos(enemy->getBoardX() + y*38,enemy->getBoardY() + x*38);
        enemy->board[x][y]=3;
        game->setWhoseTurn(enemy->getName());
    }
    else {
            std::cout << "promasaj" << std::endl;
            p->setPixmap(QPixmap(":/images/images/splash.png"));
            p->setPos(enemy->getBoardX() + y*38,enemy->getBoardY() + x*38);

            enemy->board[x][y]=2;
            game->setWhoseTurn(enemy->getName());
    }

    p->show();
    game->scene->addItem(p);

}

void Player::setBoardX(int x){
    this->boardx=x;
}

void Player::setBoardY(int y){
    this->boardy=y;
}

int Player::getBoardX(){
    return this->boardx;
}

int Player::getBoardY(){
    return this->boardy;
}
