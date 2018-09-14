#include "shark.h"


int Shark::type() const
{
        return Type;
}

Shark::Shark(FishType type, const QPointF pos):FishModel(type, pos)
{
    setSwimPicture();
    setHungryDelta();
    setHungryPicture();
    setGrownTarget();
    setDiePicture();

    setStep(2.5);

    AllTimerReady();
}

QRectF Shark::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-80 - penwidth/2, -80 - penwidth/2, 160 + penwidth, 160 + penwidth);
}

void Shark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (m_condition) {
    case normal:
        if (target.x() > now.x()) {
            painter->drawPixmap(-80, -80, 160, 160, *pic_swim_mirror, 0 + frame*160 , 0, 160, 160);
        }
        else painter->drawPixmap(-80, -80, 160, 160, *pic_swim, 0 + frame*160 , 0, 160, 160);
        break;
    case FishCondition::hungry:
        if (target.x() > now.x()) {
            painter->drawPixmap(-80, -80, 160, 160, *pic_swim_mirror, 0 + frame*160 , 160, 160, 160);
        }
        else painter->drawPixmap(-80, -80, 160, 160, *pic_swim, 0 + frame*160 , 160, 160, 160);
        break;
    case die:
        painter->drawPixmap(-80, -80, 160, 160, *pic_swim, 0 + frame*160 , 480, 160, 160);
        break;
    default:
        break;
    }
}

void Shark::eat(qreal hunger, qreal grow)
{
    hungry = hungry+hunger;
    if (hungry>140) hungry = 140;
}

void Shark::setHungryDelta()
{
    hungryDelta = 0.225;
}

void Shark::setGrownTarget()
{
    grownTarget = 1000;
}

void Shark::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/fish/Bmeat_all.png");
    pic_swim_mirror = new QPixmap(":/img/fish/Bmeat_all_mirror.png");
}

void Shark::setHungryPicture()
{
    pic_hungry = new QPixmap(":/img/fish/Bmeat_all.png");
    pic_hungry_mirror = new QPixmap(":/img/fish/Bmeat_all_mirror.png");
}

void Shark::setDiePicture()
{
    pic_die = new QPixmap(":/img/fish/Bmeat_all.png");
    pic_die_mirror = new QPixmap(":/img/fish/Bmeat_all_mirror.png");
}
