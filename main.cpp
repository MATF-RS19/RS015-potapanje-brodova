#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "battleshipgame.h"
#include <iostream>

BattleshipGame *game;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    game = new BattleshipGame();
    game->show();
    game->displayMenu();

    QObject::connect(&a, SIGNAL(aboutToQuit()), game, SLOT(beforeExit()));

    return a.exec();
}
