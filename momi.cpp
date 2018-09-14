#include "momi.h"

int Momi::type() const
{
    return Type;
}

Momi::Momi(FishType type, const QPointF pos) : FishModel(type, pos)
{
    setSwimPicture();
    setHungryDelta();
    setHungryPicture();
    setGrownTarget();
    setDiePicture();

    if (type == moderatemomi){
        setIntervalGiven(20000);
    } else{
        setIntervalGiven(10000);
    }

    setStep(1.5);

    AllTimerReady();
}

QRectF Momi::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void Momi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    switch (m_condition) {
    case normal:
        if (target.x() > now.x()) {
            painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 0 + (static_cast<int>(m_type-smallmomi)*3) *80 , 80, 80);
        }
        else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 + (static_cast<int>(m_type-smallmomi)*3) *80 , 80, 80);
        break;
    case FishCondition::hungry:
        if (target.x() > now.x()) {
            painter->drawPixmap(-40, -40, 80, 80, *pic_hungry_mirror, 0 + frame*80 , 0 + (static_cast<int>(m_type-smallmomi)) *80 + 720 , 80, 80);
        }
        else painter->drawPixmap(-40, -40, 80, 80, *pic_hungry, 0 + frame*80 , 0 +(static_cast<int>(m_type-smallmomi)) *80 +720 , 80, 80);
        break;
    case die:
        painter->drawPixmap(-40, -40, 80, 80, *pic_die, 0 + frame*80 , 0 + (static_cast<int>(m_type-smallmomi)*3 + 2)*80 , 80, 80);
        break;
    default:
        break;
    }
}

void Momi::eat(qreal hunger, qreal grow)
{
    hungry = hungry+hunger;
    if (hungry>100) hungry = 100;
    if (m_type == bigmomi) return;
    growing+=grow;
    if (growing >=grownTarget){
        timer->stop();
        give_timer->stop();
        emit ImGrown(this);
    }
}

void Momi::setHungryDelta()
{
    switch (m_type) {
    case smallmomi:
        hungryDelta = 0.4;
        break;
    case moderatemomi:
        hungryDelta = 0.3;
        break;
    case bigmomi:
        hungryDelta = 0.25;
        break;
    default:
        break;
    }
}

void Momi::setGrownTarget()
{
    switch (m_type) {
    case smallmomi:
        grownTarget = 5;
        break;
    case moderatemomi:
        grownTarget = 16;
        break;
    case bigmomi:
        grownTarget = 20;
        break;
    default:
        break;
    }
}

void Momi::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/fish/momi_swim.png");
    pic_swim_mirror = new QPixmap(":/img/fish/momi_swim_mirror.png");
}

void Momi::setHungryPicture()
{
    pic_hungry = new QPixmap(":/img/fish/momi_hungry.png");
    pic_hungry_mirror = new QPixmap(":/img/fish/momi_hungry_mirror.png");
}

void Momi::setDiePicture()
{
    pic_die = new QPixmap(":/img/fish/momi_hungry.png");
    pic_die_mirror = new QPixmap(":/img/fish/momi_hungry_mirror.png");
}
