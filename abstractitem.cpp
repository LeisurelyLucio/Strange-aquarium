#include "abstractitem.h"

AbstractItem::AbstractItem() : frame(0),
    m_type(small), x(0), y(0),
    pic(NULL), step(10),
    timer(NULL)
{
}

AbstractItem::~AbstractItem()
{
}

bool AbstractItem::isColliding()
{
    return false;
}

QRectF AbstractItem::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-20 - penwidth/2, -20 - penwidth/2, 40 + penwidth, 40 + penwidth);
}

void AbstractItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-20, -20, 40, 40, QPixmap(":/img/item/food.png"), 0 +static_cast<int>(m_type) *40 , 0 + frame*40 , 40, 40);
}


