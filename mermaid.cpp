#include "mermaid.h"

int Mermaid::type() const
{
    return Type;
}

Mermaid::Mermaid(PetType type, const QPointF pos) : PetModel(type, pos)
{
    setSwimPicture();

    setTarget(QPointF(700, 520));
    setStep(3.5);

    setIntervalGiven(25000);

    AllTimerReady();
}

QRectF Mermaid::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void Mermaid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (target.x() > now.x()) {
        painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 0 , 80, 80);
    }
    else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 , 80, 80);
}

void Mermaid::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/pet/meryl.png");
    pic_swim_mirror = new QPixmap(":/img/pet/meryl_mirror.png");
}
