#include "battleshipgame.h"

BattleshipGame::BattleshipGame(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,800);

    scene = new QGraphicsScene();

    scene->setSceneRect(0,0,800,800);

    setScene(scene);
}

void BattleshipGame::start(){
    scene->clear();
    cellBoard1= new cellBoard();
    cellBoard2= new cellBoard();
    cellBoard1->placeBoard(100,350,10,10);
    cellBoard2->placeBoard(400,350,10,10);

}