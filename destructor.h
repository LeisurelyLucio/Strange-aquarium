#ifndef DESTRUCTOR_H
#define DESTRUCTOR_H

#include "alienmodel.h"

class Destructor : public AlienModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 19 };   //外星生物类型声明
    int type() const;

    Destructor(AlienType type = destructor);


    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void Rua(AlienModel*);

protected slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void sendMissile();
    void Rua();
protected:
    virtual void setSwimPicture();
};

#endif // DESTRUCTOR_H
