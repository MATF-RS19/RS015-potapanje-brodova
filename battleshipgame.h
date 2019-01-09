#ifndef BATTLESHIPGAME_H
#define BATTLESHIPGAME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "cellboard.h"
#include "player.h"



class BattleshipGame: public QGraphicsView
{
    Q_OBJECT

public:
    BattleshipGame(QWidget* parent=NULL);
    void start();
    void setWhoseTurn(QString);
    QGraphicsScene* scene;
    cellBoard* cellBoard1;
    cellBoard* cellBoard2;
    Player* player1;
    Player* player2;

private:
    QString whoseTurn="player1";
};

#endif // BATTLESHIPGAME_H
