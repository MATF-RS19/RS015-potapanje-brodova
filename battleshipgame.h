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


class BattleshipGame: public QGraphicsView
{
    Q_OBJECT

public:
    BattleshipGame(QWidget* parent=NULL);
    ServerCommunicator interface;
    void setWhoseTurn(QString);
    QGraphicsScene* scene;
    Player* player1;
    Player* player2;
    QString getWhoseTurn(void);
    bool getFinishedPlacing();
    void setFinishedPlacing(bool b);
    void displayMenu();
    QPushButton* playButton;
    QPushButton* lockButton;
    QPushButton* createButton;
    QLineEdit* textName;
    std::vector<string> games;



public slots:
    void start();
    void editText();
    void lock();
    void lobby();

private:
    QString whoseTurn;
    bool finishedPlacing= false;

};

#endif // BATTLESHIPGAME_H
