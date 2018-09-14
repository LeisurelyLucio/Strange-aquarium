#ifndef MSCENE_H
#define MSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>
#include "fooditem.h"
#include "gold.h"
#include "gubi.h"
#include "meatfish.h"
#include "momi.h"
#include "shark.h"
#include "snails.h"
#include "mermaid.h"
#include "dolphin.h"
#include "bang.h"
#include "feeder.h"
#include "tuna.h"
#include "bluemonster.h"
#include "foodie.h"
#include "destructor.h"
#include "missile.h"
#include "boss.h"

#define bossflag 1
#define snailsflag 2
#define mermaidflag 4
#define dolphinflag 8
#define bangflag 16
#define feederflag 32
#define tunaflag 64

class Mscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Mscene(int &init_gold, QRectF now, int flag = 0, QObject *parent = 0);
    ItemType GetQuality(){ return quality; }

protected:
    //void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void goldChanged();
    void MonsterBGM();
    void FeedBGM();
    void BossBGM();

public slots:
    void createNewFish(FishType type, QPointF pos);
protected slots:
    void gold_changed();
    void foodNum_changed();
    void foodQuality_changed();
    void foodOverFlow(FoodItem*);
    void goldPicked(Gold*);
    void fish_hungry(FishModel* now);
    void fish_die(FishModel*);
    void fishGrown(FishModel* now);
    void createNewMoney(ItemType type, QPointF pos);
    void createNewFood(QPointF pos);
    void createNewPet(PetType type, QPointF pos);
    void PetAiming(PetModel*);
    void PetGiving(PetType type, QPointF pos);
    void productCoin(FishType type, QPointF pos);
    void ImMonster();
    void MonsterDie(AlienModel*);
    void MonsterAiming(AlienModel*);
    void MonsterRua(AlienModel*);
    void createMissile(AlienModel*);

private:
    int& gold_num;
    int foodTotalNumber;
    int foodTopNumber;
    int frame;
    int attack_count;
    int  monstercount;
    ItemType quality;
    QTimer *timer;

};

#endif // MSCENE_H
