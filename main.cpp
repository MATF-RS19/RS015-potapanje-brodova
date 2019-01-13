#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "battleshipgame.h"

BattleshipGame *game;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    game = new BattleshipGame();
    game->show();
    game->displayMenu();
    const int ret = a.exec();
    delete game;
    return ret;
}
