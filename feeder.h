#ifndef FEEDER_H
#define FEEDER_H

#include "petmodel.h"

class Feeder : public PetModel
{
    Q_OBJECT
 public:
     enum { Type = UserType + 13 };   //宠物类型声明
     int type() const;

     Feeder(PetType type = feeder, const QPointF pos = QPointF(300, 220));
     int hungry_function() { if (feed_condition) return 100; else return 0; }
     int grown_function() { if (feed_condition) return 3; else return 0; }
     bool getCondition() { return feed_condition; }
     void resetCondition() { feed_condition = false; }

     virtual QRectF boundingRect() const;
     virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

 protected:
    virtual void setSwimPicture();
    bool feed_condition;

protected slots:
     void setCondition();

};

#endif // FEEDER_H
