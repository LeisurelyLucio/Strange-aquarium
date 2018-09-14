#ifndef TUNA_H
#define TUNA_H

#include "petmodel.h"

class Tuna : public PetModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 13 };   //宠物类型声明
    int type() const;

    Tuna(PetType type = tuna, const QPointF pos = QPointF(600, 40));

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int hungry_function() { return 30; }
    void setCondition() { isAttacking = true; setStep(15); }
    void resetCondition() { isAttacking = false; setStep(2);}
    bool getCondition() { return isAttacking; }

protected:
    virtual void setSwimPicture();
    bool isAttacking;

};

#endif // TUNA_H
