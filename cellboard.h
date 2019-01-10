#ifndef CELLBOARD_H
#define CELLBOARD_H

#include <QList>
#include "cell.h"

/*pretrazeno mnogo sajtova i kodova za ideju
 *nekoliko repozitorijuma na githabu su sluzili kao inspiracija
 * btw nije debagovano,moguce greske
*/


class cellBoard
{
public:
    cellBoard();
    QList<Cell*> getCells();
    void placeBoard(int,int,int,int);
    void setPlayerName(QString playerName);
    QString getPlayerName(void);
private:
    QList<Cell*> cells;
    void createColumn(int,int,int,int);
    QString playerName;
};

#endif // CELLBOARD_H
