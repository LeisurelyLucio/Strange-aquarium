#ifndef FOODITEM_H
#define FOODITEM_H


#include "abstractitem.h"

class FoodItem : public AbstractItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 15 };  //食物类型声明
    int type() const;
    bool isDelete;

    FoodItem(const QPointF &point = QPointF(100, 100), ItemType type = small);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qreal hungry_function();
    qreal grow_function();

    ~FoodItem();

signals:
    void overFlow(FoodItem*);

protected slots:
    void fall();

protected:
    virtual bool isColliding() override;

};

#endif // FOODITEM_H
