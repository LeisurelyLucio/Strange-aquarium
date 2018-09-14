#include "petmodel.h"

PetModel::PetModel(PetType type, const QPointF pos)
{
    //随机事件初始化
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()) + qrand()%10);

    frame = 0;
    timer_interval = 7000;
    stay_frame = 0;
    m_type = type;

    step = 3;
    target.setX((qrand()%900)+10);
    target.setY((qrand()%500)+10);
    now.setX(pos.x());
    now.setY(pos.y());
    setPos(pos);
}

QRectF PetModel::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void PetModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (target.x() > now.x()) {
        painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 0 , 80, 80);
    }
    else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 , 80, 80);
}

void PetModel::setTarget(QPointF x)
{
    target.setX(x.x());
    target.setY(x.y());
}

PetModel::~PetModel()
{
    timer->stop();
    give_timer->stop();

    delete timer;
    delete give_timer;

    delete pic_swim;
    delete pic_swim_mirror;
}

void PetModel::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/pet/stinky.png");
    pic_swim_mirror = new QPixmap(":/img/pet/stinky_mirror.png");
}

qreal PetModel::getDistance(QPointF &now, QPointF &target)
{
    return sqrt((now.x()-target.x())*(now.x()-target.x()) + (now.y()-target.y())*(now.y()-target.y()));
}

void PetModel::setMove(qreal accelate)
{
    qreal x=target.x()-now.x();
    qreal y=target.y()-now.y();
    qreal dx = accelate*step*x / sqrt(x*x + y*y);
    qreal dy = accelate*step*y / sqrt(x*x + y*y);
    now.setX(now.x()+dx);
    now.setY(now.y()+dy);
    setPos(now);
}

void PetModel::AllTimerReady()
{
    timer = new QTimer(this);
    give_timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(swim()));
    timer->setInterval(50);
    timer->start();

    connect(give_timer, SIGNAL(timeout()), this, SLOT(ImGiving()));
    give_timer->setInterval(timer_interval);
    give_timer->start();
}

void PetModel::swim()
{
    stay_frame++;
    if (stay_frame>=6){
        stay_frame = 0;
        emit newTarget(this);
    }
    frame = (frame+1)%10;
    if (getDistance(now, target) >= step) {
        setMove(1);
    } else{
        setPos(now);
    }
}

void PetModel::ImGiving()
{
    emit ImGiven(m_type, now);
}
