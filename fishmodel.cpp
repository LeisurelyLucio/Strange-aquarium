#include "fishmodel.h"


FishModel::FishModel(FishType type, const QPointF pos)
{
    //随机事件初始化
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()) + qrand()%10);

    frame = 0;
    timer_interval = 14000;
    stay_frame = 0;
    m_type = type;
    m_condition = normal;

    step = 2;
    target.setX((qrand()%900)+10);
    target.setY((qrand()%500)+10);
    now.setX(pos.x());
    now.setY(pos.y());
    setPos(pos);

    hungry = 100;
    heart = 3;
    growing = 0;   
}

QRectF FishModel::boundingRect() const
{
    qreal penwidth = 1;  //防止笔宽产生影响
    return QRectF(-40 - penwidth/2, -40 - penwidth/2, 80 + penwidth, 80 + penwidth);
}

void FishModel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

void FishModel::setTarget(QPointF x)
{
    target.setX(x.x());
    target.setY(x.y());
}

void FishModel::attacked(int delta)
{
    heart -= delta;
    if (heart<=0) ImDie();
}

void FishModel::eat(qreal hunger, qreal grow)
{
    hungry = hungry+hunger;
    if (hungry>100) hungry = 100;
    growing+=grow;
    if (growing >=grownTarget){
        timer->stop();
        give_timer->stop();
        emit ImGrown(this);
    }
}

void FishModel::ImDie()
{
    timer->stop();
    give_timer->stop();
    emit ImDied(this);
}

FishModel::~FishModel()
{
    timer->stop();
    give_timer->stop();

    delete timer;
    delete give_timer;

    delete pic_swim;
    delete pic_die;
    delete pic_hungry;
    delete pic_swim_mirror;
    delete pic_die_mirror;
    delete pic_hungry_mirror;
}

void FishModel::setHungryDelta()
{
    hungryDelta = 0.4;
}

void FishModel::setGrownTarget()
{
    grownTarget = 3;
}

void FishModel::setSwimPicture()
{
    pic_swim = new QPixmap(":/img/fish/swim.png");
    pic_swim_mirror = new QPixmap(":/img/fish/swim_mirror.png");
}

void FishModel::setHungryPicture()
{
    pic_hungry = new QPixmap(":/img/fish/hungry.png");
    pic_hungry_mirror = new QPixmap(":/img/fish/hungry_mirror.png");
}

void FishModel::setDiePicture()
{
    pic_die = new QPixmap(":/img/fish/die.png");
    pic_die_mirror = new QPixmap(":/img/fish/die_mirror.png");
}

qreal FishModel::getDistance(QPointF &now, QPointF &target)
{
    return sqrt((now.x()-target.x())*(now.x()-target.x()) + (now.y()-target.y())*(now.y()-target.y()));
}

void FishModel::setMove(qreal accelate)
{
    qreal x=target.x()-now.x();
    qreal y=target.y()-now.y();
    qreal dx = accelate*step*x / sqrt(x*x + y*y);
    qreal dy = accelate*step*y / sqrt(x*x + y*y);
    now.setX(now.x()+dx);
    now.setY(now.y()+dy);
    setPos(now);
}

void FishModel::AllTimerReady()
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

void FishModel::setIntervalGiven(int x)
{
    timer_interval = x;
}

int FishModel::type() const
{
    return Type;
}

void FishModel::swim()
{
    hungry -= hungryDelta;
    if (hungry >= 50) {
        //处理正常
        m_condition = normal;
        frame = (frame+1)%10;
        if (getDistance(now, target) <= step){
            stay_frame++;
            if (stay_frame>=10){
                stay_frame = 0;
                target.setX((qrand()%900)+10);
                target.setY((qrand()%500)+10);
            }
        } else{
            setMove(1);
        }
    }
    else if (hungry <= 0) {
        //处理死亡
        if (m_condition != die){
            m_condition = die;
            frame = 0;
            stay_frame = 0;
        } else{
            if (stay_frame>=14) {
                ImDie();
                return;
            }
            if (frame == 9) stay_frame++;
            else frame++;
        }
        moveBy(0, step);

    } else{
        //处理饥饿
        m_condition = FishCondition::hungry;
        frame = (frame+1)%10;
        if (frame == 0) emit ImHungry(this);
        setMove(1 +  (51 - hungry) / 25.0);
    }
}

void FishModel::ImGiving()
{
    emit ImGiven(m_type, now);
}
