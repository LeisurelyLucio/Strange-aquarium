#include "bluemonster.h"

int BlueMonster::type() const
{
    return Type;
}

BlueMonster::BlueMonster(AlienType type) : AlienModel()
{
    m_type = type;
    hungry = 800;

    now.setX(qrand()%800+100);
    now.setY(qrand()%350+100);
    setPos(now);

    setStep(4);
    setSwimPicture();
    AllTimerReady();
}

QRectF BlueMonster::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void BlueMonster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (target.x() > now.x()) {
        painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 0 , 80, 80);
    }
    else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 , 80, 80);
}

void BlueMonster::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;

    QPointF pos = event->scenePos();
    if (pos.x()<now.x()) now.setX(now.x()+20);
    else now.setX(now.x()-20);
    if (pos.y()<now.y()) now.setY(now.y()+20);
    else now.setY(now.y()-20);
    setPos(now);

    eat(80);

    event->accept();
}

void BlueMonster::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/alien/smallsylv.png");
    pic_swim_mirror = new QPixmap(":/img/alien/smallsylv_mirror.png");
}
