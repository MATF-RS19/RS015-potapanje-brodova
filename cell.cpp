#include "cell.h"
#include <QVector>
#include <QPointF>
#include "battleshipgame.h"
#include <string>
#include <QGraphicsPixmapItem>
#include "config.h"

extern BattleshipGame* game;

Cell::Cell(QGraphicsItem* parent){
    QRect c=QRect(QPoint(0,0),QPoint(35,35));
    QRectF cell(c);

    setRect(cell);
    isPlaced=false;
}

void Cell::setIsPlaced(bool b)
{
    this->isPlaced=b;
}
void Cell::setCoords(int x,int y){
    this->x_coord = x;
    this->y_coord = y;
}
bool Cell::getIsPlaced(){
    return isPlaced;
}
int Cell::getX(){
    return x_coord;
}
int Cell::getY(){
    return y_coord;
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent* event){

    if(event->button()==Qt::LeftButton){
        if(game->getFinishedPlacing()){
            if(game->getWhoseTurn()== game->player1->getName())
            {
                game->player1->takeTurn(this->getX(),this->getY(),this->getPlayerName());
            }


            else // wtf
            {
                game->player1->takeTurn(this->getX(),this->getY(),this->getPlayerName());
            }
        }
        else{
            if(game->player1->shipsPlaced == NUMBER_OF_SHIPS)
            {
                std::cout << "ships already placed" << std::endl;
                return;
            }
            else
            {
                if(game->player1->board[this->getX()][this->getY()] == 1){
                    return;
                }
                game->player1->board[this->getX()][this->getY()] = 1;
                game->player1->shipsPlaced += 1;

                setState(1);

                if(game->player1->shipsPlaced == NUMBER_OF_SHIPS){
                    game->lockButton->setEnabled(true);
                }
                std::cout << "ship placed at : " << this->getX() << "," << this->getY() << ". Placed " << game->player1->shipsPlaced << " ships" << std::endl;
            }
        }
    }
    if(event->button()==Qt::RightButton)
    {
        if(game->getFinishedPlacing()){
            return;
        }
        else
        {
            if(game->player1->board[this->getX()][this->getY()] == 1){
                game->player1->board[this->getX()][this->getY()] = 0;
                game->player1->shipsPlaced--;
                this->setOpacity(1);
                setState(0);
                std::cout << "removed ship at : " << this->getX() << "," << this->getY() << " Placed" << game->player1->shipsPlaced << "ships" << std::endl;
                game->lockButton->setEnabled(false);

            }
        }
    }
}

void Cell::setPlayerName(QString playerName){
    this->playerName=playerName;
}

QString Cell::getPlayerName(void){
    return this->playerName;
}

void Cell::setState(int state) {
    if (state == 0) {
        setBrush(Qt::white);
    } else if (state == 1) {
        QImage ship(":/images/images/ship.png");
        QBrush brush(ship);
        setBrush(brush);
    } else if (state == 2) {
        QImage ship(":/images/images/splash.png");
        QBrush brush(ship);
        setBrush(brush);
    } else if (state == 3) {
        QImage ship(":/images/images/fire.png");
        QBrush brush(ship);
        setBrush(brush);
    }
}

