#include "destructor.h"

int Destructor::type() const
{
    return Type;
}

Destructor::Destructor(AlienType type) : AlienModel()
{
    m_type = type;
    hungry = 1000;
    setStep(2);
    setSwimPicture();

    target.setY(480);
    now.setX(qrand()%800+100);
    now.setY(480);
    setPos(now);

    AllTimerReady();
}

QRectF Destructor::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-80 - penwidth/2, -80 - penwidth/2, 160 + penwidth, 160 + penwidth);
}

void Destructor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (target.x() > now.x()) {
        painter->drawPixmap(-80, -80, 160, 160, *pic_swim_mirror, 0 + frame*160 , 0 , 160, 160);
    }
    else painter->drawPixmap(-80, -80, 160, 160, *pic_swim, 0 + frame*160 , 0 , 160, 160);
}

void Destructor::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;

    eat(60);

    event->accept();
}

void Destructor::sendMissile()
{
    emit Rua(this);
}

void Destructor::Rua()
{
    sendMissile();
}

void Destructor::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/alien/destructor.png");
    pic_swim_mirror = new QPixmap(":/img/alien/destructor_mirror.png");
}
