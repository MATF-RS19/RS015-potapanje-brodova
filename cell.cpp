#include "cell.h"
#include <QVector>
#include <QPointF>


Cell::Cell(){
    QRect c=QRect(QPoint(0,0),QPoint(20,20));
    QRectF cell(c);

    setRect(cell);
    isPlaced=false;
}

void Cell::setIsPlaced(bool b)
{
    this->isPlaced=b;
}
void Cell::setCoords(int x,int y){
    x_cord = x;
    y_cord = y;
}
bool Cell::getIsPlaced(){
    return isPlaced;
}
bool Cell::getX(){
    return x_cord;
}
bool Cell::getY(){
    return y_cord;
}

