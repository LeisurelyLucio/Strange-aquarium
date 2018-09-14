#ifndef ALIENMODEL_H
#define ALIENMODEL_H

#include <QPainter>
#include <QPixmap>
#include <QGraphicsObject>
#include <QTimer>
#include <QTime>
#include <QGraphicsSceneMouseEvent>

enum AlienType{ monster = 0, foodie, destructor, missile, boss};

class AlienModel : public QGraphicsObject
{
    Q_OBJECT
public:
    AlienModel();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTarget(QPointF x = QPointF((qrand()%900)+10, (qrand()%500)+10));
    void eat(qreal hunger);
    void ImDie();
    AlienType getType(){ return m_type; }

    ~AlienModel();

signals:
    void ImDied(AlienModel*);
    void newTarget(AlienModel*);

protected:
    qreal hungry;
    int frame,stay_frame, showTime;
    QPointF target, now;
    qreal step;
    AlienType m_type;
    QPixmap *pic_swim, *pic_swim_mirror;
    QTimer *timer, *rua_timer;
    bool isDied;

    virtual void setSwimPicture();

    qreal getDistance(QPointF &a, QPointF &b);
    void setMove(qreal accelate);
    void setStep(qreal x){ step = x; }
    void AllTimerReady();


protected slots:
    void swim();
    virtual void Rua() { return; }

};

#endif // ALIENMODEL_H
