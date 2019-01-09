#include <QGraphicsTextItem>
#include "battleshipgame.h"
#include <stdlib.h>
#include <time.h>
#include <QPushButton>
#include <QGraphicsProxyWidget>

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
    playButton->hide();
    scene->clear();
    cellBoard1= new cellBoard();
    cellBoard2= new cellBoard();
    cellBoard1->placeBoard(100,350,10,10);
    cellBoard2->placeBoard(400,350,10,10);
    player1 = new Player();
    player2 = new Player();
    player1->setName("player1");
    player2->setName("player2");
    srand(time(NULL));
    int random1=rand()%10;
    int random2=rand()%10;

    player1->board[random1][random2] = 1;
    for(int i=0;i<10;i++){
        for(int j =0;j<10;j++)
            std::cout << player1->board[i][j] << " ";
        std::cout << std::endl;
    }




// sinhronizacija grafickih polja sa board poljem u playeru ( dodati atribut name u cellBoard radi sinhronizacije)

// ispisivati ciji je potez

// zabraniti kliktanje na protivnicko polje u toku postavljanja brodova i zabraniti kliktanje na sopstveno polje u toku svog poteza

// upisivanje imena

// lista trenutnih igara

}

void BattleshipGame::setWhoseTurn(QString whoseTurn){
    this->whoseTurn=whoseTurn;
}

QString BattleshipGame::getWhoseTurn(){
    return whoseTurn;
}


void BattleshipGame::setFinishedPlacing(bool b){
    finishedPlacing=b;
}

bool BattleshipGame::getFinishedPlacing(){
    return finishedPlacing;
}

void BattleshipGame::displayMenu(){

    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Battleship online"));
    int tx = 100;
    int ty = 150;
    title->setPos(tx,ty);
    scene->addItem(title);

    playButton = new QPushButton("PLAY",this);
    int bx=100;
    int by=250;
    playButton->setGeometry(bx,by,50,25);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    playButton->show();
}


/*void BattleshipGame::lock(){
    if(player1->shipsPlaced != 5 && player2->shipesPlaced != 5){
        return;
    }
    else{

    }
}
*/
