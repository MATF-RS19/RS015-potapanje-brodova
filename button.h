#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>


class Button: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Button(QString str,int w,int h,int id,QGraphicsItem* parent=NULL);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    int id;

signals:
    void clicked();

private:
    QGraphicsTextItem* name;
};

#endif // BUTTON_H
