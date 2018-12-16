#ifndef CELL_H
#define CELL_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

using namespace std;

class Cell : public QGraphicsRectItem
{


private:
    bool isPlaced;
    int x_cord;
    int y_cord;
public:
    Cell();
    bool getIsPlaced();
    bool getX();
    bool getY();

    void setIsPlaced(bool b);
    void setCoords(int x,int y);
};

#endif // CELL_H
