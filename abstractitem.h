#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include <QPainter>
#include <QPixmap>
#include <QGraphicsObject>
#include <QTimer>

enum ItemType { small = 0, moderate, large, so_many, special };

class AbstractItem : public QGraphicsObject
{
    Q_OBJECT
public:
    AbstractItem();
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    ItemType getmType() { return m_type; };
    ItemType setmType(ItemType now) { m_type = now; };
    ~AbstractItem();

protected:
    int frame,stay_frame,timer_interval;
    qreal x,y, step;
    ItemType m_type;
    QPixmap *pic;
    QTimer *timer;

    virtual bool isColliding();
};

#endif // ABSTRACTITEM_H
