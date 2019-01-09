#include "cell.h"
#include <QVector>
#include <QPointF>
#include "battleshipgame.h"
#include <string>

extern BattleshipGame* game;

Cell::Cell(QGraphicsItem* parent){
    QRect c=QRect(QPoint(0,0),QPoint(20,20));
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
        if(game->getWhoseTurn()== "player1"){

            game->player1->takeTurn(game->player2,this->getX(),this->getY());
        }
        else{

            game->player2->takeTurn(game->player1,this->getX(),this->getY());
        }
    }
}

