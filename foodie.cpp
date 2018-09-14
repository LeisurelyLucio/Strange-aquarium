#include "foodie.h"

int Foodie::type() const
{
    return Type;
}

Foodie::Foodie(AlienType type) : AlienModel()
{
    m_type = foodie;
    hungry = 900;
    setStep(1.5);
    setSwimPicture();

    now.setX(qrand()%800+100);
    now.setY(qrand()%350+100);
    setPos(now);

    AllTimerReady();
}

QRectF Foodie::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-80 - penwidth/2, -80 - penwidth/2, 160 + penwidth, 160 + penwidth);
}

void Foodie::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (target.x() > now.x()) {
        painter->drawPixmap(-80, -80, 160, 160, *pic_swim_mirror, 0 + frame*160 , 0 , 160, 160);
    }
    else painter->drawPixmap(-80, -80, 160, 160, *pic_swim, 0 + frame*160 , 0 , 160, 160);
}

void Foodie::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/alien/gus.png");
    pic_swim_mirror = new QPixmap(":/img/alien/gus_mirror.png");
}
