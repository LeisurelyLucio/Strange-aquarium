#ifndef MERMAID_H
#define MERMAID_H

#include "petmodel.h"

class Mermaid : public PetModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 13 };   //宠物类型声明
    int type() const;

    Mermaid(PetType type = mermaid, const QPointF pos = QPointF(500, 520));

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    virtual void setSwimPicture();
};

#endif // MERMAID_H
