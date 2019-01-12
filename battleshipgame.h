#ifndef BATTLESHIPGAME_H
#define BATTLESHIPGAME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
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
    Player* player2;
    std::vector<string> games;

    QString getWhoseTurn(void);
    void setWhoseTurn(QString);
    bool getFinishedPlacing();
    void setFinishedPlacing(bool b);

    void displayMenu();

    QGraphicsScene* scene;
    QPushButton* playButton;
    QPushButton* lockButton;
    QPushButton* createButton;
    QLineEdit* textName;

public slots:
    void start();
    void editText();
    void lock();
    void lobby();
};

#endif // BATTLESHIPGAME_H
