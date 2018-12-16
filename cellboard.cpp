#include "cellboard.h"
#include <QBrush>

/*posto sam definisao kvadrat da bude duzine 20, mora da bude veci razmak od toga posto se racuna
gornjeg levog coska kvadrata */
#define SPACE 25


cellBoard::cellBoard()
{

}


QList<Cell *> cellBoard::getCells(){
    return cells;
}

void cellBoard::placeBoard(int x,int y,int cols,int rows){
    for(int i=0,n=cols;i<n;i++){
        createColumn(SPACE*i + x,y,rows,i);
    }
}


void cellBoard::createColumn(int x,int y,int numOfrows,int curr_i){
    //x i y ce sluziti za gui poziciju na sceni
    for(int i=0;i<numOfrows;i++){
        Cell* cell = new Cell();
        cell->setIsPlaced(true);
        cell->setCoords(i,curr_i);

        cells.append(cell);

       //TODO dodati na scenu
    }
}
