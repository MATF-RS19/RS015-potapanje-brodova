#include "player.h"
#include "battleshipgame.h"
#include "cellboard.h"
#include "config.h"
#include <unistd.h>
#include <thread>
extern BattleshipGame* game;

Player::Player() {
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            this->board[i][j]=0;
        }
    }
    shipsPlaced=0;
}

void Player::setName(QString name){
    this->name=name;
}

QString Player::getName(){
    return name;
}

void Player::setSecret(QString secret){
    this->secret = secret;
}

QString Player::getSecret(){
    return secret;
}
void Player::initGame(string _gameID) {
    gameID = _gameID;
}

void Player::pollGameState() {
    cout << "Starting to poll game state" << endl;
    std::thread([this]() {
        while (gameID != "") {
            try {
                string response = interface.getGameState(
                        name.toStdString(),
                        secret.toStdString(),
                        gameID
                );
         //       cout << response << endl << endl;
                istringstream newState{response};
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        string cell;
                        newState >> cell;
                        if (board[i][j] != stoi(cell)) {
                            cellboard->getCells()[j * BOARD_SIZE + i]->setState(stoi(cell));
                            board[i][j] = stoi(cell);
                        }
                    }
                }
                for (int i = 0; i < BOARD_SIZE; i++) {
                    for (int j = 0; j < BOARD_SIZE; j++) {
                        string cell;
                        newState >> cell;
                        if (enemyBoard[i][j] != stoi(cell)) {
                            enemyCellBoard->getCells()[j * BOARD_SIZE + i]->setState(stoi(cell));
                            enemyBoard[i][j] = stoi(cell);
                        }
                    }
                }
                string turn;
                newState >> turn;
                game->setWhoseTurn(QString::fromStdString(turn));
                string state;
                newState >> state;

                if(state == "playing" && game->getWhoseTurn() != this->getName()){
                    game->basicTurnText->setText("Enemy Turn");
                }
                if(state == "playing" && game->getWhoseTurn() == this->getName()){
                    game->basicTurnText->setText("Your Turn");
                }

                cout << "Game state: " << state << ", turn: " << turn << endl;
                if(state == "won"){
                    this->WinnerStatus = "won";
                    this->gameID = "";
                }
                if(state == "lost"){
                    this->WinnerStatus = "lost";
                    this->gameID = "";
                }
                string enemyName;
                newState >> enemyName;

                game->viewport()->update();
            } catch (string const err) {
                cerr << "Error: " << err << endl;
            }
            usleep(1000000); // mikrosekunde
        }
        cout << "Stopped polling game state" << endl;
        game->endGame();
    }).detach();


}

bool Player::isHit(int x,int y){
    if(this->board[x][y] == 1){
        this->board[x][y]=3;
        return true;
    }
    this->board[x][y]=2;
    return false;
}


void Player::takeTurn(int x, int y,QString player){

    if(game->getWhoseTurn() != this->getName()){
        return;
    }

    if(this->getEnemyName() != player){ // wtf
        return;
    }

    if(this->enemyBoard[x][y] ==2 || this->enemyBoard[x][y] == 3){
        return;
    }

    std::cout << "polje" << x << " " << y << "gadja :" << game->getWhoseTurn().toStdString() << std::endl;

    try {
        string newCellState = interface.playTurn(name.toStdString(), secret.toStdString(), gameID, x, y);
        if (enemyBoard[x][y] != stoi(newCellState)) {
            enemyCellBoard->getCells()[y * BOARD_SIZE + x]->setState(stoi(newCellState));
            enemyBoard[x][y] = stoi(newCellState);
        }
        game->setWhoseTurn(this->getEnemyName());
        game->basicTurnText->setText("Enemy Turn");
    } catch (string const err) {
        cerr << err << endl;
    }
}

void Player::setBoardX(int x){
    this->boardx=x;
}

void Player::setBoardY(int y){
    this->boardy=y;
}

int Player::getBoardX(){
    return this->boardx;
}

int Player::getBoardY(){
    return this->boardy;
}

QString Player::getEnemyName(){
    return this->enemyName;
}

void Player::setEnemyName(QString name){
    this->enemyName = name;
}

void Player::setBoardXE(int xe){
    this->boardxe=xe;
}
void Player::setBoardYE(int ye){
    this->boardye=ye;
}
int Player::getBoardXE(){
    return this->boardxe;
}
int Player::getBoardYE(){
    return this->boardye;
}

