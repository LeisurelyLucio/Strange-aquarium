#ifndef GOLD_H
#define GOLD_H

#include "abstractitem.h"
#include <QGraphicsSceneMouseEvent>

class Gold : public AbstractItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 14 };  //钱币类型声明
    int type() const;

    Gold(int &gold_now, const QPointF &point = QPointF(100, 100), ItemType type = small);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void pick_start();

    ~Gold();
private:
    int& gold;    
    bool isPicked;

signals:
    void gold_changed();
    void ImPicked(Gold*);

protected slots:
    void fall();
    void picking();

protected:
    QTimer *timer_pick;
    virtual bool isColliding() override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GOLD_H
