#include "feeder.h"

int Feeder::type() const
{
    return Type;
}

Feeder::Feeder(PetType type, const QPointF pos) : PetModel(type, pos)
{
    setSwimPicture();

    setTarget(QPointF(400, 220));
    setStep(2.5);
    feed_condition = false;

    setZValue(1);

    setIntervalGiven(10000);

    AllTimerReady();
    connect(give_timer, SIGNAL(timeout()), this, SLOT(setCondition()));
}

QRectF Feeder::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void Feeder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (feed_condition){
        if (target.x() > now.x()) {
            painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 80 , 80, 80);
        }
        else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 80 , 80, 80);
    } else{
        if (target.x() > now.x()) {
            painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 0 , 80, 80);
        }
        else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 , 80, 80);
    }
}

void Feeder::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/pet/prego.png");
    pic_swim_mirror = new QPixmap(":/img/pet/prego_mirror.png");
}

void Feeder::setCondition()
{
    feed_condition = true;
}
