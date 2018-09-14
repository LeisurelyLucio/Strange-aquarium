#ifndef GUBI_H
#define GUBI_H

#include "fishmodel.h"

class Gubi : public FishModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 16 };   //素食鱼类型声明
    int type() const;

    Gubi(FishType type = smallgubi, const QPointF pos = QPointF(500, 200));

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void eat(qreal hunger, qreal grow);

protected:
    virtual void setHungryDelta();
    virtual void setGrownTarget();
    virtual void setSwimPicture();
    virtual void setHungryPicture();
    virtual void setDiePicture();
};

#endif // GUBI_H
