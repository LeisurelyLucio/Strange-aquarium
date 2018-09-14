#ifndef MEATFISH_H
#define MEATFISH_H

#include "fishmodel.h"

class MeatFish : public FishModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 17 };   //肉食鱼类型声明
    int type() const;

    MeatFish(FishType type = meatfish, const QPointF pos = QPointF(500, 200));

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

#endif // MEATFISH_H
