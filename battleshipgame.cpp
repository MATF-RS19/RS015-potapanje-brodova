#include "battleshipgame.h"
#include <stdlib.h>
#include <time.h>

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
    player1 = new Player();
    srand(time(NULL));
    int random1 = rand() % 10;
    int random2 = rand() % 10;

    std::cout << "started, " << random1 <<" " <<  random2<< std::endl;

    player1->board[random1][random2] = 1;
    for(int i=0;i<10;i++){
        for(int j =0;j<10;j++)
            std::cout << player1->board[i][j] << " ";
        std::cout << std::endl;
    }


}

void BattleshipGame::setWhoseTurn(QString whoseTurn){
    this->whoseTurn=whoseTurn;
}
