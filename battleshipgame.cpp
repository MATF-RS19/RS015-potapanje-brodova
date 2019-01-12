#include <QGraphicsTextItem>
#include "battleshipgame.h"
#include <stdlib.h>
#include <time.h>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include "ServerCommunicator.h"
#include <QImage>
#include "config.h"
#include <vector>
#include <string>
#include <QLabel>
#include <button.h>

BattleshipGame::BattleshipGame(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200,800);

    scene = new QGraphicsScene();

    scene->setSceneRect(0,0,1200,800);

    QImage bg(":/images/images/bg.jpeg");
    QBrush brush(bg);
    scene->setBackgroundBrush(brush);

    setScene(scene);
}

void BattleshipGame::start(){
    setFinishedPlacing(true);
    lockButton->hide();
    player2 = new Player();
    player2->setName("player2");
    std::cout << "player1 name = " << player1->getName().toStdString() << std::endl;

    try {
        string ships;
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                if (player1->board[i][j])
                    ships += to_string(i) + "," + to_string(j) + ",";

        // TODO obrisati

        player2->cellboard->setPlayerName(player2->getName());
        player2->setBoardX(700);
        player2->setBoardY(350);
        player2->cellboard->placeBoard(700,350,10,10);
        srand(time(NULL));
        setWhoseTurn(player1->getName());
    } catch (string const err) {
        cerr << err << endl;
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
    connect(playButton,SIGNAL(clicked()),this,SLOT(lobby()));
    playButton->show();
    playButton->setEnabled(false);

    textName = new QLineEdit;
    textName->setPlaceholderText("Enter your name");
    textName->setFocus();
    scene->addWidget(textName);
    connect(textName,SIGNAL(textChanged(QString)),this,SLOT(editText()));
}


void BattleshipGame::lobby(){
    try {
        QString name = textName->text();

        string secret = interface.registerUser(name.toStdString());
        cout <<"secret:" <<secret << endl;

        player1 = new Player();
        player1->setName(name);
        player1->setSecret(QString::fromStdString(secret));
        player1->cellboard->setPlayerName(player1->getName());
        player1->setBoardX(100);
        player1->setBoardY(350);

        playButton->hide();
        scene->clear();

        createButton = new QPushButton("CREATE",this);
        int bx=700;
        int by=250;
        createButton->setGeometry(bx,by,50,25);
        connect(createButton,SIGNAL(clicked()),this,SLOT(lock()));
        createButton->show();
        createButton->setEnabled(true);

        games.clear();
        games = interface.getOpenGames();

        QGraphicsRectItem* panel = new QGraphicsRectItem(100,100,500,300);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::white);
        panel->setBrush(brush);
        panel->setOpacity(1);
        scene->addItem(panel);
        QGraphicsTextItem* label;
        Button* button;
        int j=0;

        for(auto i = games.begin(); i != games.end() ;j++, i++){
           label = scene->addText(QString::fromStdString(*i));
           label->setPos(102,102+20*j);
           button = new Button(QString("Join"),50,20,j);
           button->setPos(400,102 + 20*j);
           connect(button,SIGNAL(clicked()),this,SLOT(lock()));
           scene->addItem(button);
        }



        } catch (string const err) {
        cerr << err << endl;
        }


}


void BattleshipGame::lock(){
    try {
        scene->clear();
        createButton->hide();
        player1->cellboard->placeBoard(100,350,10,10);

        lockButton = new QPushButton("LOCK",this);
        int bx=100;
        int by=250;
        lockButton->setGeometry(bx,by,50,25);
        connect(lockButton,SIGNAL(clicked()),this,SLOT(start()));
        lockButton->show();
        lockButton->setEnabled(false);

        std::cout << player1->gameID << std::endl;

    } catch (string const err) {
        cerr << err << endl;
    }
}

void BattleshipGame::editText(){
    if(!textName->text().isEmpty())
        playButton->setEnabled(true);
    else
        playButton->setEnabled(false);
}
