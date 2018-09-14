#include "gold.h"

int Gold::type() const
{
    return Type;
}

Gold::Gold(int &gold_now, const QPointF &point, ItemType type) :
    gold(gold_now)
{
    frame = 0;
    stay_frame = 0;
    pic = new QPixmap(":/img/item/money.png");
    step = 1.5;

    isPicked = false;
    m_type = type;    
    x = point.x();
    y = point.y();
    setPos(point);

    timer = new QTimer(this);
    timer_pick = new QTimer(this);
    timer_interval = 50;
    connect(timer, SIGNAL(timeout()), this, SLOT(fall()));
    connect(timer_pick, SIGNAL(timeout()), this, SLOT(picking()));
    timer->setInterval(timer_interval);
    timer_pick->setInterval(17);
    timer->start();
}

QRectF Gold::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-20 - penwidth/2, -20 - penwidth/2, 40 + penwidth, 40 + penwidth);
}

void Gold::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-36, -36, 72, 72, *pic, 0 + frame*72 , 0 + static_cast<int>(m_type) *72 , 72, 72);
}

Gold::~Gold()
{
    timer->stop();
    timer_pick->stop();
    delete timer;
    delete timer_pick;
    delete pic;
}

void Gold::pick_start()
{
    if (isPicked) return;
    isPicked = true;
    switch (m_type){
    case small:
        gold+=15;
        break;
    case moderate:
        gold+=35;
        break;
    case large:
        gold+=200;
        break;
    case so_many:
        gold+=2000;
        break;
    case special:
        gold+=350;
        break;
    default:
        break;
    }
    emit gold_changed();

    frame = 0;
    timer_pick->start();
}

void Gold::fall()
{
    if (y>560) {
        if (stay_frame!=0){
            emit ImPicked(this);
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

void Gold::picking()
{
    qreal dx= 6 * step * (950 - x) / sqrt((950-x)*(950-x) + (-50-y)*(-50-y));
    qreal dy= 6 * step * (-50-y) / sqrt((950-x)*(950-x) + (-50-y)*(-50-y));

    x+=dx;
    y+=dy;
    moveBy(dx, dy);

    if (x>=900 && y<= 0){
        emit ImPicked(this);
    }
}

bool Gold::isColliding()
{
    return false;
}

void Gold::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;

    pick_start();

    event->accept();
}
