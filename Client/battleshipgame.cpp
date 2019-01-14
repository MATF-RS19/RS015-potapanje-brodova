#include <QGraphicsTextItem>
#include "battleshipgame.h"
#include <stdlib.h>
#include <time.h>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include "ServerCommunicator.h"
#include <QImage>
#include "../config.h"
#include <vector>
#include <string>
#include <QLabel>
#include "button.h"

BattleshipGame::BattleshipGame(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1200,800);
    setWindowTitle("Battleships Online");

    scene = new QGraphicsScene();

    scene->setSceneRect(0,0,1200,800);

    QImage bg(":images/bg.jpeg");
    QBrush brush(bg);
    scene->setBackgroundBrush(brush);

    //inicijalizacija svih widget-a koji ce biti korisceni vise puta

    basicTurnText = new QLabel("Finding an opponent", this);
    basicTurnText->hide();

    errorLabel = new QLabel("", this);
    errorLabel->hide();
    errorLabel->setAlignment(Qt::AlignCenter);
    errorLabel->setGeometry(0, 0, 1200, 30);
    errorLabel->setStyleSheet("\
        background-color: #F55624;\
        color: white;\
        font-size: 16px;\
    ");

    hideErrorButton = new QPushButton("x",this);
    hideErrorButton->setGeometry(1170, 0, 30, 30);
    hideErrorButton->setFlat(true);
    hideErrorButton->setStyleSheet("\
        background-color: transparent;\
        color: white;\
    ");
    connect(hideErrorButton,SIGNAL(clicked()),this,SLOT(hideError()));
    hideErrorButton->hide();

    playButton = new QPushButton("PLAY",this);
    connect(playButton,SIGNAL(clicked()),this,SLOT(lobby()));
    playButton->hide();

    refreshButton = new QPushButton("REFRESH",this);
    connect(refreshButton,SIGNAL(clicked()),this,SLOT(loadGames()));
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

    //pocetak igre

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

        //provera da li je igrac kreirao igru ili se pridruzuje vec postojecoj igri

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


        player1->setEnemyName(QString(""));
        std::cout << "enemy name = " << player1->getEnemyName().toStdString() << std::endl;

        player1->enemyCellBoard->setPlayerName(player1->getEnemyName());
        player1->setBoardXE(750);
        player1->setBoardYE(350);
        player1->enemyCellBoard->placeBoard(player1->getBoardXE(), player1->getBoardYE(), BOARD_SIZE, BOARD_SIZE);

        viewport()->update();
    } catch (string const err) {
        cerr << err << endl;
        showError(err);
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

    //pocetni ekran po pokretanju aplikacije

    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Battleships Online"));
    int tx = width()/4;
    int ty = 50;
    title->setPos(tx,ty);
    title->setScale(5);
    QFont font = title->font();
    font.setBold(true);
    title->setFont(font);
    scene->addItem(title);

    int bx=this->width()/2-50;
    int by=4*this->height()/6;
    playButton->setGeometry(bx,by,100,50);
    playButton->show();
    playButton->setEnabled(false);

    //potrebno upisivanje imena radi registracije na serveru

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

        //provera da li je igrac vec inicijalizovan i inicijalizacija (ili resetovanje) svih ostalih potrebnih objekata i promenljivih

        if(!isPlayerCreated){
            QString name = textName->text();
            string _name = name.toStdString();
            _name.erase(std::remove_if(_name.begin(), _name.end(), [](char c) { return !std::isalnum(c); }), _name.end());
            name = QString::fromStdString(_name);
            cout << _name << endl;

            if (_name == "") return;

            hideError();
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
        loadGames();
    } catch (string const err) {
        cerr << err << endl;
        showError(err);
    }
}


void BattleshipGame::lock(){
    try {

        //iscrtava se tabla i postavljaju se brodici

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
        showError(err);
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
    if(player1->WinnerStatus == "won") {
        basicTurnText->setText(QString("Congratulations, you won!"));
    } else if(player1->WinnerStatus == "lost") {
        basicTurnText->setText(QString("Sorry to inform you, you lost"));
    } else {
        basicTurnText->setText(QString("The other player seems to have disconnected"));
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
}


void BattleshipGame::loadGames(){

    //ispis trenutno slobodnih igara na serveru

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

    for(auto game = games.begin(); game != games.end() ;j++, game++) {
        string gameId = game->first;
        string creator = game->second;
        label = scene->addText(QString::fromStdString(creator + "'s game"));
        label->setPos(152, 102 + 25 * j);
        button = new Button(QString("Join"), 50, 20, j);
        button->setPos(495, 105 + 25 * j);
        connect(button, SIGNAL(clicked()), this, SLOT(lock()));
        scene->addItem(button);
    }

    viewport()->update();
}

void BattleshipGame::showError(string error) {
    errorLabel->setText(QString::fromStdString(error));
    errorLabel->show();
    hideErrorButton->show();
}

void BattleshipGame::hideError() {
    errorLabel->hide();
    hideErrorButton->hide();
}

void BattleshipGame::beforeExit() {
    if (isPlayerCreated) {
        cout << "Unregistering..." << endl;
        interface.unregister(player1->getName().toStdString(), player1->getSecret().toStdString());
    }
}
