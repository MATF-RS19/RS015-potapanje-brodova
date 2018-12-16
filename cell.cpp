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
