#ifndef BLUEMONSTER_H
#define BLUEMONSTER_H

#include "alienmodel.h"

class BlueMonster : public AlienModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 19 };   //外星生物类型声明
    int type() const;

    BlueMonster(AlienType type = monster);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected:
    virtual void setSwimPicture();

};

#endif // BLUEMONSTER_H
