#ifndef FOODIE_H
#define FOODIE_H

#include "alienmodel.h"

class Foodie : public AlienModel
{   
    Q_OBJECT
public:
    enum { Type = UserType + 19 };   //外星生物类型声明
    int type() const;

    Foodie(AlienType type = foodie);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    virtual void setSwimPicture();

};

#endif // FOODIE_H
