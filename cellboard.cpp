#include "cellboard.h"
#include <QBrush>
#include "battleshipgame.h"
#include "config.h"

/*posto sam definisao kvadrat da bude duzine 20, mora da bude veci razmak od toga posto se racuna
gornjeg levog coska kvadrata */

#define SPACE 38

extern BattleshipGame* game;


cellBoard::cellBoard()
{

}


QList<Cell*> cellBoard::getCells(){
    return cells;
}

void cellBoard::placeBoard(int x,int y,int cols,int rows){
    for(int i=0,n=cols;i<n;i++){
        createColumn(SPACE*i + x,y,rows,i);
    }
}


void cellBoard::createColumn(int x,int y,int numOfrows,int curr_i){

    for(int i=0;i<numOfrows;i++){
        Cell* cell = new Cell();
        cell->setPlayerName(this->getPlayerName());
        cell->setPos(x,y+SPACE*i);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::white);
        cell->setBrush(brush);

        cell->setIsPlaced(true);
        cell->setCoords(i,curr_i);

        cells.append(cell);

        game->scene->addItem(cell);

    }
}

void cellBoard::setPlayerName(QString playerName){
    this->playerName=playerName;
}

QString cellBoard::getPlayerName(){
    return this->playerName;
}
