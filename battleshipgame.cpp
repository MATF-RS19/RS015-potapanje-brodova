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

    basicTurnText = new QLabel("Finding an opponent", this);
    basicTurnText->hide();

    playButton = new QPushButton("PLAY",this);
    connect(playButton,SIGNAL(clicked()),this,SLOT(lobby()));
    playButton->hide();

    refreshButton = new QPushButton("Refresh",this);
    connect(refreshButton,SIGNAL(clicked()),this,SLOT(refresh()));
    refreshButton->hide();

    createButton = new QPushButton("CREATE",this);
    connect(createButton,SIGNAL(clicked()),this,SLOT(lock()));
    createButton->hide();

    lockButton = new QPushButton("LOCK",this);
    connect(lockButton,SIGNAL(clicked()),this,SLOT(start()));
    lockButton->hide();

    returnToLobby = new QPushButton("LOBBY",this);
    connect(returnToLobby,SIGNAL(clicked()),this,SLOT(lobby()));
    returnToLobby->hide();



    textName = new QLineEdit;



    setScene(scene);
}

void BattleshipGame::start(){
    setFinishedPlacing(true);
    lockButton->hide();
    std::cout << "player1 name = " << player1->getName().toStdString() << std::endl;
    basicTurnText->setText("Waiting for opponent");
    basicTurnText->setAlignment(Qt::AlignCenter);
    basicTurnText->setGeometry(0, 300, 1200, 30);
    basicTurnText->show();
    try {
        string ships;
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                if (player1->board[i][j])
                    ships += to_string(i) + "," + to_string(j) + ",";
        if (player1->gameID == "") {
            string gameId = interface.createGame(
                    player1->getName().toStdString(),
                    player1->getSecret().toStdString(),
                    ships
            );
            cout << "Created game ID: " << gameId << endl;
            player1->initGame(gameId);
            player1->pollGameState();
        } else {
            string str = interface.joinGame(
                    player1->getName().toStdString(),
                    player1->getSecret().toStdString(),
                    player1->gameID,
                    ships
            );
            setWhoseTurn(player1->getName());
            player1->pollGameState();
        }


        player1->setEnemyName(QString("enemy"));
        std::cout << "enemy name = " << player1->getEnemyName().toStdString() << std::endl;

        player1->enemyCellBoard->setPlayerName(player1->getEnemyName());
        player1->setBoardXE(700);
        player1->setBoardYE(350);
        player1->enemyCellBoard->placeBoard(player1->getBoardXE(), player1->getBoardYE(), BOARD_SIZE, BOARD_SIZE);

        srand(time(NULL));
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

    int bx=100;
    int by=250;
    playButton->setGeometry(bx,by,50,25);
    playButton->show();
    playButton->setEnabled(false);

    textName->setPlaceholderText("Enter your name");
    textName->setFocus();
    scene->addWidget(textName);
    connect(textName,SIGNAL(textChanged(QString)),this,SLOT(editText()));
}


void BattleshipGame::lobby(){
    try {
        if(!isPlayerCreated){
            QString name = textName->text();
            string _name = name.toStdString();
            _name.erase(std::remove_if(_name.begin(), _name.end(), [](char c) { return !std::isalnum(c); }), _name.end());
            name = QString::fromStdString(_name);
            cout << _name << endl;

            if (_name == "") return;

            string secret = interface.registerUser(name.toStdString());
            cout << "secret: " << secret << endl;

            createPlayer(name,secret);
        }
        if(!playButton->isHidden()){
            playButton->hide();
        }
        if(!returnToLobby->isHidden()){
            returnToLobby->hide();
        }
        if(!basicTurnText->isHidden()){
            basicTurnText->hide();
        }
        scene->clear();

        player1->cellboard = new cellBoard();
        player1->enemyCellBoard = new cellBoard();
        player1->cellboard->setPlayerName(player1->getName());
        player1->setBoardX(100);
        player1->setBoardY(350);
        player1->WinnerStatus="";

        setFinishedPlacing(false);
        for(int i=0;i<BOARD_SIZE;i++){
            for(int j=0;j<BOARD_SIZE;j++){
                player1->board[i][j]=0;
            }
        }
        player1->shipsPlaced=0;

        int bx=700;
        int by=250;
        createButton->setGeometry(bx,by,50,25);

        createButton->show();
        createButton->setEnabled(true);

        int rx=700;
        int ry=280;
        refreshButton->setGeometry(rx,ry,50,25);
        refreshButton->show();
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
        player1->cellboard->placeBoard(player1->getBoardX(),player1->getBoardY(),BOARD_SIZE,BOARD_SIZE);

        int bx=100;
        int by=250;
        lockButton->setGeometry(bx,by,50,25);

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


void BattleshipGame::endGame(){
    //congradulations, you win or you lose
    scene->clear();
    if(player1->WinnerStatus == "won"){
        basicTurnText->setText(QString("Congradulations,you won"));
    }
    else{
        basicTurnText->setText(QString("Sorry to inform you, you lost"));
    }

    int bx=200;
    int by=250;
    returnToLobby->setGeometry(bx,by,70,35);
    returnToLobby->show();
    returnToLobby->setEnabled(true);

}


void BattleshipGame::createPlayer(QString name,string secret){

    player1 = new Player();
    player1->setName(name);
    player1->setSecret(QString::fromStdString(secret));
    isPlayerCreated=true;
    cout << isPlayerCreated << endl;

}


void BattleshipGame::refresh(){
    scene->clear();
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

}
