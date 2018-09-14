#ifndef PETMODEL_H
#define PETMODEL_H

#include <QPainter>
#include <QPixmap>
#include <QGraphicsObject>
#include <QTimer>
#include <QTime>

enum PetType{ snails = 0, mermaid, dolphin, bang, feeder, tuna };

class PetModel : public QGraphicsObject
{
    Q_OBJECT
public:
    PetModel(PetType type = snails, QPointF pos = QPointF(500, 520));

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTarget(QPointF x = QPointF((qrand()%900)+10, 520));
    PetType getPetType(){ return m_type; }

    ~PetModel();

signals:
    void ImGiven(PetType, QPointF);
    void newTarget(PetModel*);

protected:
    int frame,stay_frame,timer_interval;
    QPointF target, now;
    qreal step;
    PetType m_type;
    QPixmap *pic_swim, *pic_swim_mirror;
    QTimer *timer, *give_timer;

    virtual void setSwimPicture();

    qreal getDistance(QPointF &a, QPointF &b);
    void setMove(qreal accelate);
    void setStep(qreal x) { step = x; }
    void AllTimerReady();
    void setIntervalGiven(int x) { timer_interval = x;}

protected slots:
    void swim();
    void ImGiving();
};

#endif // PETMODEL_H
