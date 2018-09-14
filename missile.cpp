#include "missile.h"

int Missile::type() const
{
    return Type;
}

Missile::Missile(QPointF pos, AlienType type) : AlienModel()
{
    m_type = type;
    hungry = 80;
    setStep(6);
    setSwimPicture();
    setPos(pos);
    now = pos;
    AllTimerReady();
}

QRectF Missile::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void Missile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal dx = target.x()-now.x();
    qreal dy = target.y()-now.y();
    if (dy == 0){
        if (dx<= 0) frame = 8;
        else frame = 0;
    } else{
        qreal tan = dx/dy;
        if (tan>=4){
            if (dx>0) frame = 0;
            else frame = 8;
        }
        if (tan>=1.5) {
            if (dx>0) frame = 15;
            else frame = 7;
        }
        else if (tan>=0.75){
            if (dx>0) frame = 14;
            else frame = 6;
        }
        else if (tan>=0.25){
            if (dx>0) frame = 13;
            else frame = 5;
        }
        else if (tan>0){
            if (dx>0) frame = 12;
            else frame = 4;
        }
        else if (tan == 0){
            if (dy>0) frame = 12;
            else frame = 4;
        }
        else if (tan >= -0.25){
            if (dx<0) frame = 12;
            else frame = 4;
        }
        else if (tan>=-0.75){
            if (dx<0) frame = 11;
            else frame = 3;
        }
        else if (tan>=-1.5){
            if (dx<0) frame = 10;
            else frame = 2;
        }
        else if (tan>=-4){
            if (dx<0) frame = 9;
            else frame = 1;
        }
        else{
            if (dx<0) frame = 8;
            else frame = 0;
        }
    }

    painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 , 80, 80);
}

void Missile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;

    eat(80);

    event->accept();
}

void Missile::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/alien/missile.png");
    pic_swim_mirror = new QPixmap(":/img/alien/missile.png");
}
