#include "cell.h"
#include <QVector>
#include <QPointF>
#include "battleshipgame.h"
#include <string>
#include <QGraphicsPixmapItem>

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
    QGraphicsPixmapItem* p = new QGraphicsPixmapItem();
    if(event->button()==Qt::LeftButton){
        if(game->getFinishedPlacing()){
            if(game->getWhoseTurn()== game->player1->getName())
            {
                game->player1->takeTurn(game->player2,this->getX(),this->getY(),this->getPlayerName());
            }


            else
            {
                game->player2->takeTurn(game->player1,this->getX(),this->getY(),this->getPlayerName());
            }
        }
        else{
            if(game->player1->shipsPlaced == 5)
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

                this->setOpacity(0.5);

                //ne izbacuje sliku????
                QPixmap map(":/images/images/ship.png");
                std::cout << "pixmap is " << map.height() << std::endl;
                p->setPixmap(map);
                p->setPos(100 + 38*this->getY(), 350 + 38*this->getX());
                p->show();
                game->scene->addItem(p);

                if(game->player1->shipsPlaced == 5){
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
                delete(p);
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


