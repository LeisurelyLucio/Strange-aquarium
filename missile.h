#ifndef MISSILE_H
#define MISSILE_H

#include "alienmodel.h"

class Missile : public AlienModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 19 };   //外星生物类型声明
    int type() const;

    Missile(QPointF pos = QPointF(520, 520), AlienType type = missile);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected:
    virtual void setSwimPicture();
};

#endif // MISSILE_H
