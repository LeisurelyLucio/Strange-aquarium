#ifndef FISHMODEL_H
#define FISHMODEL_H

#include <QPainter>
#include <QPixmap>
#include <QGraphicsObject>
#include <QTimer>
#include <QTime>

enum FishType{ smallgubi=0, moderategubi, biggubi, kinggubi, meatfish, smallmomi, moderatemomi, bigmomi, shark };
enum FishCondition{ normal = 0, hungry, die};

class FishModel : public QGraphicsObject
{
    Q_OBJECT

public:
    enum { Type = UserType + 16 };   //素食鱼类型声明
    int type() const;

    FishModel(FishType type = smallgubi, const QPointF pos = QPointF(500, 200));

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTarget(QPointF x = QPointF((qrand()%900)+10, (qrand()%500)+10));
    void attacked(int delta = 1);
    virtual void eat(qreal hunger, qreal grow);
    void ImDie();
    FishType getType(){ return m_type; }
    FishCondition getCondition(){ return m_condition; }

    qreal hungry_function(){ return 80; }   //食用价值
    qreal grow_function(){ return 0; }  //食用价值

    ~FishModel();

signals:
    void ImHungry(FishModel*);
    void ImGrown(FishModel *);
    void ImGiven(FishType, QPointF);
    void ImDied(FishModel*);

protected:
    qreal hungry, hungryDelta, heart, growing, grownTarget;
    int frame,stay_frame,timer_interval;
    QPointF target, now;
    qreal step;
    FishType m_type;
    FishCondition m_condition;
    QPixmap *pic_swim, *pic_hungry, *pic_die;
    QPixmap *pic_swim_mirror, *pic_hungry_mirror, *pic_die_mirror;
    QTimer *timer, *give_timer;

    virtual void setHungryDelta();
    virtual void setGrownTarget();
    virtual void setSwimPicture();
    virtual void setHungryPicture();
    virtual void setDiePicture();

    qreal getDistance(QPointF &a, QPointF &b);
    void setMove(qreal accelate);
    void setStep(qreal x){ step = x; }
    void AllTimerReady();
    void setIntervalGiven(int x);

protected slots:
    void swim();
public slots:
    void ImGiving();
};

#endif // FISHMODEL_H
