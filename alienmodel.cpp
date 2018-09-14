#include "alienmodel.h"

AlienModel::AlienModel()
{
    setZValue(2);

    //随机事件初始化
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()) + qrand()%10);

    frame = 0;
    stay_frame = 0;
    showTime = 0;
    isDied = false;

    m_type = static_cast<AlienType>(qrand()%2);

    step = 3;
    target.setX((qrand()%900)+10);
    target.setY((qrand()%500)+10);

    hungry = 800;
}

QRectF AlienModel::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void AlienModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (target.x() > now.x()) {
        painter->drawPixmap(-40, -40, 80, 80, *pic_swim_mirror, 0 + frame*80 , 0 , 80, 80);
    }
    else painter->drawPixmap(-40, -40, 80, 80, *pic_swim, 0 + frame*80 , 0 , 80, 80);
}

void AlienModel::setTarget(QPointF x)
{
    target.setX(x.x());
    target.setY(x.y());
}

void AlienModel::eat(qreal hunger)
{
    hungry = hungry-hunger;
    if (hungry<=0) {
        ImDie();
    }
}

void AlienModel::ImDie()
{
    if (isDied) return;
    isDied = true;
    timer->stop();
    rua_timer->stop();
    emit ImDied(this);
}

AlienModel::~AlienModel()
{
    timer->stop();
    rua_timer->stop();

    delete rua_timer;
    delete timer;

    delete pic_swim;
    delete pic_swim_mirror;
}

void AlienModel::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/alien/smallsylv.png");
    pic_swim_mirror = new QPixmap(":/img/alien/smallsylv_mirror.png");
}

qreal AlienModel::getDistance(QPointF &now, QPointF &target)
{
    return sqrt((now.x()-target.x())*(now.x()-target.x()) + (now.y()-target.y())*(now.y()-target.y()));
}

void AlienModel::setMove(qreal accelate)
{
    qreal x=target.x()-now.x();
    qreal y=target.y()-now.y();
    qreal dx = accelate*step*x / sqrt(x*x + y*y);
    qreal dy = accelate*step*y / sqrt(x*x + y*y);
    now.setX(now.x()+dx);
    now.setY(now.y()+dy);
    setPos(now);
}

void AlienModel::AllTimerReady()
{
    timer = new QTimer(this);
    rua_timer = new QTimer(this);
    rua_timer->setInterval(7000);
    rua_timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(swim()));
    connect(rua_timer, SIGNAL(timeout()), this, SLOT(Rua()));
    timer->setInterval(50);
    timer->start();
}

void AlienModel::swim()
{
    stay_frame++;
    if (stay_frame>=8){
        stay_frame = 0;
        emit newTarget(this);
    }

    frame = (frame+1)%10;

    if (hungry >= 50) {
        //处理正常
        if (getDistance(now, target) >= step)
            setMove(1);
    } else{
        //处理濒死
       if (getDistance(now, target) >= step)
            setMove(1 +  (51 - hungry) / 15.0);
    }
}
