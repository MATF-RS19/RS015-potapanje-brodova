#include <QGraphicsTextItem>
#include "battleshipgame.h"
#include <stdlib.h>
#include <time.h>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QLineEdit>

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
    if(!getFinishedPlacing()){
        return;
    }
    player2 = new Player();
    player2->setName("player2");
    std::cout << "player1 name = " << player1->getName().toStdString() << std::endl;

    player2->cellboard->setPlayerName(player2->getName());
    player2->cellboard->placeBoard(400,350,10,10);
    srand(time(NULL));
    setWhoseTurn(player1->getName());

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
    connect(playButton,SIGNAL(clicked()),this,SLOT(lock()));
    playButton->show();
    playButton->setEnabled(false);


    textName = new QLineEdit;
    textName->setPlaceholderText("Enter your name");
    textName->setFocus();
    scene->addWidget(textName);
    connect(textName,SIGNAL(textChanged(QString)),this,SLOT(editText()));
}


void BattleshipGame::lock(){
    player1 = new Player();
    QString name = textName->text();
    player1->setName(name);
    player1->cellboard->setPlayerName(player1->getName());

    playButton->hide();
    scene->clear();

    player1->cellboard->placeBoard(100,350,10,10);

    lockButton = new QPushButton("LOCK",this);
    int bx=100;
    int by=250;
    lockButton->setGeometry(bx,by,50,25);
    connect(lockButton,SIGNAL(clicked()),this,SLOT(start()));
    lockButton->show();
    lockButton->setEnabled(false);


}

void BattleshipGame::editText(){
    if(!textName->text().isEmpty())
        playButton->setEnabled(true);
    else
        playButton->setEnabled(false);
}
