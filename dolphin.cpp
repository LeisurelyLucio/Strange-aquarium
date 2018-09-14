#include "dolphin.h"

int Dolphin::type() const
{
    return Type;
}

Dolphin::Dolphin(PetType type, const QPointF pos) : PetModel(type, pos)
{
    setSwimPicture();

    setTarget(QPointF(400, 220));
    setStep(4.5);

    setZValue(1);

    setIntervalGiven(30000);

    AllTimerReady();
}

QRectF Dolphin::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void Dolphin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (target.x() > now.x()) {
        painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 0 , 80, 80);
    }
    else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 , 80, 80);
}

void Dolphin::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/pet/blip.png");
    pic_swim_mirror = new QPixmap(":/img/pet/blip_mirror.png");
}
