#ifndef BATTLESHIPGAME_H
#define BATTLESHIPGAME_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include "cellboard.h"
#include "player.h"



class BattleshipGame: public QGraphicsView
{
    Q_OBJECT

public:
    BattleshipGame(QWidget* parent=NULL);
    void setWhoseTurn(QString);
    QGraphicsScene* scene;
    cellBoard* cellBoard1;
    cellBoard* cellBoard2;
    Player* player1;
    Player* player2;
    QString getWhoseTurn(void);
    bool getFinishedPlacing();
    void setFinishedPlacing(bool b);
    void displayMenu();
    QPushButton* playButton;

public slots:
    void start();
   // void lock();

private:
    QString whoseTurn="player1";
    bool finishedPlacing= false;
};

#endif // BATTLESHIPGAME_H
