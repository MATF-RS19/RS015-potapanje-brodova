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

    refreshButton = new QPushButton("REFRESH",this);
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
    basicTurnText->setGeometry(0, 300, 1200, 35);
    QFont font = basicTurnText->font();
    font.setBold(true);
    font.setPointSize(25);
    basicTurnText->setFont(font);
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
        player1->setBoardXE(750);
        player1->setBoardYE(350);
        player1->enemyCellBoard->placeBoard(player1->getBoardXE(), player1->getBoardYE(), BOARD_SIZE, BOARD_SIZE);

        viewport()->update();
    } catch (string const err) {
        cerr << err << endl;
    }

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
    int tx = width()/4;
    int ty = 50;
    title->setPos(tx,ty);
    title->setScale(5);
    scene->addItem(title);

    int bx=this->width()/2-50;
    int by=4*this->height()/6;
    playButton->setGeometry(bx,by,100,50);
    playButton->show();
    playButton->setEnabled(false);

    textName->setPlaceholderText("Enter your name");
    textName->setFocus();
    textName->setAlignment(Qt::AlignCenter);
    textName->setGeometry(this->width()/2-200,this->height()/2,400,50);
    textName->setTextMargins(10,10,10,10);
    scene->addWidget(textName);
    connect(textName,SIGNAL(textChanged(QString)),this,SLOT(editText()));

    viewport()->update();
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
        player1->setBoardX(150);
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
        int by=375;
        createButton->setGeometry(bx,by,100,50);
        createButton->show();
        createButton->setEnabled(true);

        int rx=700;
        int ry=125;
        refreshButton->setGeometry(rx,ry,100,50);
        refreshButton->show();
        games.clear();
        games = interface.getOpenGames();

        QGraphicsRectItem* panel = new QGraphicsRectItem(150,100,400,600);
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
           label->setPos(152,102+20*j);
           button = new Button(QString("Join"),50,20,j);
           button->setPos(500,102 + 20*j);
           connect(button,SIGNAL(clicked()),this,SLOT(lock()));
           scene->addItem(button);
        }

        viewport()->update();
    } catch (string const err) {
        cerr << err << endl;
    }
}


void BattleshipGame::lock(){
    try {
        scene->clear();
        createButton->hide();
        refreshButton->hide();
        player1->cellboard->placeBoard(player1->getBoardX(),player1->getBoardY(),BOARD_SIZE,BOARD_SIZE);

        int bx=150;
        int by=280;
        lockButton->setGeometry(bx+3*38,by,77,40);

        lockButton->show();
        lockButton->setEnabled(false);

        std::cout << player1->gameID << std::endl;

        viewport()->update();
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
        basicTurnText->setText(QString("Congratulations,you won"));
    }
    else{
        basicTurnText->setText(QString("Sorry to inform you, you lost"));
    }

    int bx=this->width()/2-50;
    int by=4*this->height()/6;
    returnToLobby->setGeometry(bx,by,100,50);
    returnToLobby->show();
    returnToLobby->setEnabled(true);

    viewport()->update();
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

    QGraphicsRectItem* panel = new QGraphicsRectItem(150,100,400,600);
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
       label->setPos(152,102+20*j);
       button = new Button(QString("Join"),50,20,j);
       button->setPos(500,102 + 20*j);
       connect(button,SIGNAL(clicked()),this,SLOT(lock()));
       scene->addItem(button);
    }

    viewport()->update();
}
