#ifndef BATTLESHIPGAME_H
#define BATTLESHIPGAME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "cellboard.h"
#include "player.h"
#include "ServerCommunicator.h"


class BattleshipGame: public QGraphicsView {
    Q_OBJECT

private:
    QString whoseTurn;
    bool finishedPlacing = false;
    ServerCommunicator interface;

public:
    BattleshipGame(QWidget* parent=NULL);

    Player* player1;
    std::vector<std::pair<string, string>> games;

    QString getWhoseTurn(void);
    void setWhoseTurn(QString);
    bool getFinishedPlacing();
    void setFinishedPlacing(bool b);
    void createPlayer(QString name,string secret);
    void showError(string);

    void displayMenu();
    void endGame();
    bool isPlayerCreated = false;
    string gameState;

    QGraphicsScene* scene;
    QPushButton* playButton;
    QPushButton* lockButton;
    QPushButton* createButton;
    QPushButton* returnToLobby;
    QPushButton* refreshButton;
    QLineEdit* textName;
    QLabel* basicTurnText;
    QLabel* errorLabel;
    QPushButton* hideErrorButton;

public slots:
    void start();
    void editText();
    void lock();
    void lobby();
    void loadGames();
    void hideError();
    void beforeExit();
};

#endif // BATTLESHIPGAME_H
