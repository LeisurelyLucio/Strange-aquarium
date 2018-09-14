#include "bang.h"

int Bang::type() const
{
    return Type;
}

Bang::Bang(PetType type, const QPointF pos) : PetModel(type, pos)
{
    setSwimPicture();

    setTarget(pos);
    setStep(0.5);

    setIntervalGiven(25000);

    AllTimerReady();
}

QRectF Bang::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void Bang::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (target.x() > now.x()) {
        painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 0 , 80, 80);
    }
    else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 , 80, 80);
}

void Bang::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/pet/niko.png");
    pic_swim_mirror = new QPixmap(":/img/pet/niko.png");
}
