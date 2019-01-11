#include "button.h"
#include <QBrush>

Button::Button(QString str,int w,int h,QGraphicsItem* parent) : QGraphicsRectItem(parent)
{
    setRect(0,0,w,h);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    name=new QGraphicsTextItem(str,this);
    int bx = rect().width() /2 - name->boundingRect().width()/2;
    int by = rect().height()/2 - name->boundingRect().height()/2;

    name->setPos(bx,by);
}


void Button::mousePressEvent(QGraphicsSceneMouseEvent* event){
    emit clicked();
}
