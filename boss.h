#ifndef BOSS_H
#define BOSS_H

#include "alienmodel.h"

class Boss : public AlienModel
{
    Q_OBJECT
public:
    enum { Type = UserType + 19 };   //外星生物类型声明
    int type() const;

    Boss(AlienType type = boss);


    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:
    void Rua(AlienModel*);

protected slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void Rua();
protected:
    virtual void setSwimPicture();
};

#endif // BOSS_H
