#include "fooditem.h"

FoodItem::FoodItem(const QPointF &point, ItemType type)
{
    frame = 0;
    timer_interval = 50;
    stay_frame = 0;
    step = 1.5;

    m_type = type;
    isDelete = false;

    x = point.x();
    y = point.y();
    setPos(point);

    pic = new QPixmap(":/img/item/food.png");

    timer = new QTimer(this);    
    connect(timer, SIGNAL(timeout()), this, SLOT(fall()));
    timer->setInterval(timer_interval);
    timer->start();
}

QRectF FoodItem::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-10 - penwidth/2, -10 - penwidth/2, 20 + penwidth, 20 + penwidth);
}

void FoodItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-20, -20, 40, 40, *pic, 0 + frame*40 , 0 + static_cast<int>(m_type) *40 , 40, 40);
}

qreal FoodItem::hungry_function()
{
    switch (m_type) {
    case small:
        return 60;
    case moderate:
        return 70;
    case large:
        return 80;
    case so_many:
        return 100;
    default:
        return 0;
    }
}

qreal FoodItem::grow_function()
{
    switch (m_type) {
    case small:
        return 1.5;
    case moderate:
        return 2;
    case large:
        return 3;
    case so_many:
        return 4;
    default:
        return 0;
    }
}

FoodItem::~FoodItem()
{    
    timer->stop();
    delete timer;
    delete pic;
}

void FoodItem::fall()
{        
    if (y>560) {        
        if (stay_frame!=0) {
            emit overFlow(this);
            stay_frame = 0;
        }
        return;
    }
    if (y>520 && stay_frame <= 3000/timer_interval){
        stay_frame++;
        return;
    }
    y += step;
    moveBy(0, step);
    frame = (frame+1)%10;
    return;
}


//目前没用
bool FoodItem::isColliding()
{

    return false;
}

int FoodItem::type() const
{
    return Type;
}
