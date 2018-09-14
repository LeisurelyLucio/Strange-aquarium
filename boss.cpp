#include "boss.h"


int Boss::type() const
{
    return Type;
}

Boss::Boss(AlienType type) : AlienModel()
{
    m_type = type;
    hungry = 40000;
    setStep(1.5);
    setSwimPicture();

    target.setY(480);
    target.setX(900);
    now.setX(900);
    now.setY(10);
    setPos(now);

    AllTimerReady();
}

QRectF Boss::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-80 - penwidth/2, -80 - penwidth/2, 160 + penwidth, 160 + penwidth);
}

void Boss::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (target.x() > now.x()) {
        painter->drawPixmap(-80, -80, 160, 160, *pic_swim_mirror, 0 + frame*160 , 0 , 160, 160);
    }
    else painter->drawPixmap(-80, -80, 160, 160, *pic_swim, 0 + frame*160 , 0 , 160, 160);
}

void Boss::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;

    eat(100);

    event->accept();
}

void Boss::Rua()
{
    emit Rua(this);
}

void Boss::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/alien/boss.png");
    pic_swim_mirror = new QPixmap(":/img/alien/boss_mirror.png");
}
