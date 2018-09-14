#include "gubi.h"

int Gubi::type() const
{
    return Type;
}

Gubi::Gubi(FishType type, const QPointF pos) : FishModel(type, pos)
{
    setSwimPicture();
    setHungryDelta();
    setHungryPicture();
    setGrownTarget();
    setDiePicture();

    AllTimerReady();
}

QRectF Gubi::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void Gubi::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void Gubi::eat(qreal hunger, qreal grow)
{
    hungry = hungry+hunger;
    if (hungry>100) hungry = 100;
    if (m_type == kinggubi) return;
    growing+=grow;
    if (growing >=grownTarget){
        timer->stop();
        give_timer->stop();
        emit ImGrown(this);
    }
}

void Gubi::setHungryDelta()
{
    switch (m_type) {
    case smallgubi:
        hungryDelta = 0.4;
        break;
    case moderategubi:
        hungryDelta = 0.3;
        break;
    case biggubi:
        hungryDelta = 0.25 - (qrand()%5)/30;
        break;
    case kinggubi:
        hungryDelta = 0.2;
        break;
    default:
        break;
    }
}

void Gubi::setGrownTarget()
{
    switch (m_type) {
    case smallgubi:
        grownTarget = 3;
        break;
    case moderategubi:
        grownTarget = 10;
        break;
    case biggubi:
        grownTarget = 16;
        break;
    case kinggubi:
        grownTarget = 100;
        break;
    default:
        break;
    }
}

void Gubi::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/fish/swim.png");
    pic_swim_mirror = new QPixmap(":/img/fish/swim_mirror.png");
}

void Gubi::setHungryPicture()
{
    pic_hungry = new QPixmap(":/img/fish/hungry.png");
    pic_hungry_mirror = new QPixmap(":/img/fish/hungry_mirror.png");
}

void Gubi::setDiePicture()
{
    pic_die = new QPixmap(":/img/fish/die.png");
    pic_die_mirror = new QPixmap(":/img/fish/die.png");
}
