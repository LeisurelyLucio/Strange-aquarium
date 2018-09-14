#ifndef DOLPHIN_H
#define DOLPHIN_H

#include "petmodel.h"

class Dolphin : public PetModel
{
    Q_OBJECT
 public:
     enum { Type = UserType + 13 };   //宠物类型声明
     int type() const;

     Dolphin(PetType type = dolphin, const QPointF pos = QPointF(500, 520));

     virtual QRectF boundingRect() const;
     virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

 protected:
     virtual void setSwimPicture();
};

#endif // DOLPHIN_H
