#include "cellboard.h"
#include <QBrush>
#include "battleshipgame.h"

/*posto sam definisao kvadrat da bude duzine 20, mora da bude veci razmak od toga posto se racuna
gornjeg levog coska kvadrata */
#define SPACE 23

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
        cell->setPos(x,y+SPACE*i);

        cell->setIsPlaced(true);
        cell->setCoords(i,curr_i);

        cells.append(cell);

        game->scene->addItem(cell);

    }
}
