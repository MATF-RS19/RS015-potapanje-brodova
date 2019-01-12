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
    enemyCellBoard = new cellBoard();
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


void Player::takeTurn(int x, int y,QString player){

    if(game->getWhoseTurn() != this->getName()){
        return;
    }

    if(this->getEnemyName() != player){
        return;
    }

    if(this->enemyBoard[x][y] ==2 || this->enemyBoard[x][y] == 3){
        return;
    }

    std::cout << "polje" << x << " " << y << "gadja :" << game->getWhoseTurn().toStdString() << std::endl;

    QGraphicsPixmapItem* p = new QGraphicsPixmapItem();

    if(this->enemyBoard[x][y]==1){
        std::cout << "pogodak" << std::endl;
        p->setPixmap(QPixmap(":/images/images/fire.png"));
        p->setPos(this->getBoardXE() + y*38,this->getBoardYE() + x*38);
        this->enemyBoard[x][y]=3;
        game->setWhoseTurn(this->getEnemyName());
    }
    else {
            std::cout << "promasaj" << std::endl;
            p->setPixmap(QPixmap(":/images/images/splash.png"));
            p->setPos(this->getBoardXE() + y*38,this->getBoardYE() + x*38);

            this->enemyBoard[x][y]=2;
            game->setWhoseTurn(this->getEnemyName());
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

QString Player::getEnemyName(){
    return this->enemyName;
}

void Player::setEnemyName(QString name){
    this->enemyName = name;
}

void Player::setBoardXE(int xe){
    this->boardxe=xe;
}
void Player::setBoardYE(int ye){
    this->boardye=ye;
}
int Player::getBoardXE(){
    return this->boardxe;
}
int Player::getBoardYE(){
    return this->boardye;
}

