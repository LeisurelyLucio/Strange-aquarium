#ifndef SHARK_H
#define SHARK_H

#include "fishmodel.h"

class Shark : public FishModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 18 };   //鲨鱼类型声明
    int type() const;

    Shark(FishType type = shark, const QPointF pos = QPointF(500, 200));

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

#endif // SHARK_H
