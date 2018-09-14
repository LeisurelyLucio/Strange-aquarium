#ifndef MOMI_H
#define MOMI_H

#include "fishmodel.h"

class Momi : public FishModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 16 };   //素食鱼类型声明
    int type() const;

    Momi(FishType type = smallmomi, const QPointF pos = QPointF(500, 200));

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

#endif // MOMI_H
