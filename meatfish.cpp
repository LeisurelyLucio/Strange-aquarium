#include "meatfish.h"

int MeatFish::type() const
{
        return Type;
}

MeatFish::MeatFish(FishType type, const QPointF pos):FishModel(type, pos)
{
    setSwimPicture();
    setHungryDelta();
    setHungryPicture();
    setGrownTarget();
    setDiePicture();

    setStep(3);

    AllTimerReady();
}

QRectF MeatFish::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void MeatFish::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (m_condition) {
    case normal:
        if (target.x() > now.x()) {
            painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 0 + static_cast<int>(m_type) *80 , 80, 80);
        }
        else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 + static_cast<int>(m_type) *80 , 80, 80);
        break;
    case FishCondition::hungry:
        if (target.x() > now.x()) {
            painter->drawPixmap(-40, -40, 80, 80, *pic_hungry_mirror, 0 + frame*80 , 0 + static_cast<int>(m_type) *80 , 80, 80);
        }
        else painter->drawPixmap(-40, -40, 80, 80, *pic_hungry, 0 + frame*80 , 0 + static_cast<int>(m_type) *80 , 80, 80);
        break;
    case die:
        painter->drawPixmap(-40, -40, 80, 80, *pic_die, 0 + frame*80 , 0 + static_cast<int>(m_type) *80 , 80, 80);
        break;
    default:
        break;
    }
}

void MeatFish::eat(qreal hunger, qreal grow)
{
    hungry = hungry+hunger;
    if (hungry>100) hungry = 100;
}

void MeatFish::setHungryDelta()
{
    hungryDelta = 0.3;
}

void MeatFish::setGrownTarget()
{
    grownTarget = 1000;
}

void MeatFish::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/fish/swim.png");
    pic_swim_mirror = new QPixmap(":/img/fish/swim_mirror.png");
}

void MeatFish::setHungryPicture()
{
    pic_hungry = new QPixmap(":/img/fish/hungry.png");
    pic_hungry_mirror = new QPixmap(":/img/fish/hungry_mirror.png");
}

void MeatFish::setDiePicture()
{
    pic_die = new QPixmap(":/img/fish/die.png");
    pic_die_mirror = new QPixmap(":/img/fish/die.png");
}
