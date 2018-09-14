#ifndef BANG_H
#define BANG_H

#include "petmodel.h"

class Bang : public PetModel
{
    Q_OBJECT
 public:
     enum { Type = UserType + 13 };   //宠物类型声明
     int type() const;

     Bang(PetType type = dolphin, const QPointF pos = QPointF(500, 520));

     virtual QRectF boundingRect() const;
     virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

 protected:
     virtual void setSwimPicture();
};

#endif // BANG_H
