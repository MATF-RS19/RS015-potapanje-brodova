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
                game->player1->board[this->getX()][this->getY()] = 1;
                game->player1->shipsPlaced++;
                std::cout << "ship placed at : " << this->getX() << "," << this->getY() << ". Placed" << game->player1->shipsPlaced << "ships" << std::endl;
                for(int i=0;i<10;i++){
                    for(int j =0;j<10;j++)
                        std::cout << game->player1->board[i][j] << " ";
                    std::cout << std::endl;
                }

            }
        }
    }
    if(event->button()==Qt::RightButton)
    {
        if(game->getFinishedPlacing()){
            for(int i=0;i<10;i++){
                for(int j =0;j<10;j++)
                    std::cout << game->player1->board[i][j] << " ";
                std::cout << std::endl;
            }

            return;
        }
        else
        {
            if(game->player1->board[this->getX()][this->getY()] == 1){
                game->player1->board[this->getX()][this->getY()] = 0;
                game->player1->shipsPlaced--;
                std::cout << "removed ship at : " << this->getX() << "," << this->getY() << ". Placed" << game->player1->shipsPlaced << "ships" << std::endl;
                for(int i=0;i<10;i++){
                    for(int j =0;j<10;j++)
                        std::cout << game->player1->board[i][j] << " ";
                    std::cout << std::endl;
                }

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


