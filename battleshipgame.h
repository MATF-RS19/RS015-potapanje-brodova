#ifndef BATTLESHIPGAME_H
#define BATTLESHIPGAME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "cellboard.h"



class BattleshipGame: public QGraphicsView
{
    Q_OBJECT

public:
    BattleshipGame(QWidget* parent=NULL);
    void start();

    QGraphicsScene* scene;
    cellBoard* cellBoard1;
    cellBoard* cellBoard2;
};

#endif // BATTLESHIPGAME_H
