#ifndef SNAILS_H
#define SNAILS_H

#include "petmodel.h"

class Snails : public PetModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 13 };   //宠物类型声明
    int type() const;

    Snails(PetType type = snails, const QPointF pos = QPointF(500, 520));

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    virtual void setSwimPicture();

};

#endif // SNAILS_H
