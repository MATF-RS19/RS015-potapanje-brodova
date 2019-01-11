#ifndef CELL_H
#define CELL_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Cell : public QGraphicsRectItem
{


private:
    bool isPlaced;
    int x_coord;
    int y_coord;
    QString playerName;

public:
    Cell(QGraphicsItem* parent = NULL);
    bool getIsPlaced();
    int getX();
    int getY();
    void setPlayerName(QString playerName);
    QString getPlayerName(void);
    QGraphicsPixmapItem* p;



    void setIsPlaced(bool b);
    void setCoords(int x,int y);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // CELL_H
