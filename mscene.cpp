#include "mscene.h"

Mscene::Mscene(int &init_gold, QRectF now, int flag, QObject *parent):
    QGraphicsScene(now, parent) , gold_num(init_gold)
{
    //随机事件初始化
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    clearFocus();

    if (flag & bossflag) {
        monstercount = 1;
        attack_count = -1;
        foodTotalNumber = 0;
        foodTopNumber = 4;
        quality = large;
        Boss* alien = new Boss;
        connect(alien, SIGNAL(ImDied(AlienModel*)), this, SLOT(MonsterDie(AlienModel*)));
        connect(alien, SIGNAL(newTarget(AlienModel*)), this, SLOT(MonsterAiming(AlienModel*)));
        connect(alien, SIGNAL(Rua(AlienModel*)), this, SLOT(MonsterRua(AlienModel*)));
        addItem(alien);
        MonsterRua(alien);

        createNewFish(smallgubi, QPointF(500, 100));
        createNewFish(smallgubi, QPointF(410, 100));
        createNewFish(kinggubi, QPointF(520, 300));
        createNewFish(bigmomi, QPointF(480, 150));
        createNewFish(meatfish, QPointF(620, 70));
        createNewFish(meatfish, QPointF(600, 370));
        createNewFish(shark, QPointF(220, 270));

        createNewPet(snails, QPointF(500, 520));
        createNewPet(mermaid, QPointF(700, 400));
        createNewPet(dolphin, QPointF(400,350));
        createNewPet(bang, QPointF(100,450));
        createNewPet(feeder, QPointF(320, 320));
        createNewPet(tuna, QPointF(600, 120));
        createNewPet(tuna, QPointF(100, 120));

    } else{
        frame = 0;
        attack_count = 0;
        monstercount = 0;
        foodTotalNumber = 0;
        foodTopNumber = 1;
        quality = small;
        createNewFish(smallgubi, QPointF(500, 100));
        createNewFish(smallgubi, QPointF(500, 300));

        if (flag & snailsflag) createNewPet(snails, QPointF(500, 520));
        if (flag & mermaidflag) createNewPet(mermaid, QPointF(700, 400));
        if (flag & dolphinflag)createNewPet(dolphin, QPointF(400,350));
        if (flag & bangflag)createNewPet(bang, QPointF(100,450));
        if (flag & feederflag)createNewPet(feeder, QPointF(320, 320));
        if (flag & tunaflag)createNewPet(tuna, QPointF(600, 120));

    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ImMonster()));
    timer->setInterval(3000);
    timer->start();

}

void Mscene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if (!event->isAccepted()) {
            if (event->button() == Qt::LeftButton) {
                // 在 Scene 上添加一个food
                    if (foodTotalNumber < foodTopNumber){ createNewFood(event->scenePos()); }
            } else if (event->button() == Qt::RightButton) {
                // 在 Scene 上添加一个宝箱
                    createNewMoney(so_many, event->scenePos());
            }
        }

}

void Mscene::gold_changed()
{
    emit goldChanged();
}

void Mscene::foodNum_changed()
{
    foodTopNumber++;
}

void Mscene::foodQuality_changed()
{
    quality = static_cast<ItemType> (quality+1);
}

void Mscene::foodOverFlow(FoodItem *now)
{
    if (!now->isDelete) {
        foodTotalNumber--;
        removeItem(now);
        now->isDelete = true;
    }
}

void Mscene::goldPicked(Gold *now)
{
    removeItem(now);
}

void Mscene::fish_hungry(FishModel *now)
{
    if (now->getCondition() != hungry) return;
    QGraphicsItem *itemToAim = NULL;
    QGraphicsItem *itemToRemove = NULL;
    if (now->type() == QGraphicsItem::UserType+16){
        //素食鱼
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == QGraphicsItem::UserType+15) {
                if (now->collidesWithItem(item)){
                    FoodItem *food = (FoodItem*)item;
                    now->eat(food->hungry_function(), food->grow_function());
                    foodOverFlow(food);
                    return;
                }
                itemToAim = item;
                break;
            }
        }
    }
    if (now->type() == QGraphicsItem::UserType+17) {
        //肉食鱼
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == QGraphicsItem::UserType+16) {
                if (((FishModel*)item)->getType() != smallgubi) continue;
                if (now->collidesWithItem(item)){
                    Gubi *food = (Gubi*)item;
                    now->eat(food->hungry_function(), food->grow_function());
                    food->ImDie();
                    return;
                }
                itemToAim = item;
                break;
            }
        }
    }

    if (now->type() == QGraphicsItem::UserType+18) {
        //鲨鱼
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == QGraphicsItem::UserType+17) {
                if (now->collidesWithItem(item)){
                    MeatFish *food = (MeatFish*)item;
                    now->eat(food->hungry_function(), food->grow_function());
                    food->ImDie();
                    return;
                }
                itemToAim = item;
                break;
            }
        }
    }

    // 将选中的食物位置作为目标坐标位置
    if (itemToAim != NULL)
        now->setTarget(itemToAim->scenePos());
    else
        now->setTarget();
}

void Mscene::fish_die(FishModel *now)
{
    removeItem(now);
}

void Mscene::createNewFish(FishType type, QPointF pos)
{
    switch (type) {
    case smallgubi:
    case moderategubi:
    case biggubi:
    case kinggubi:
    {
        Gubi* fish = new Gubi(type, pos);
        connect(fish, SIGNAL(ImGrown(FishModel*)), this, SLOT(fishGrown(FishModel*)));
        connect(fish, SIGNAL(ImHungry(FishModel*)), this, SLOT(fish_hungry(FishModel*)));
        connect(fish, SIGNAL(ImGiven(FishType,QPointF)), this, SLOT(productCoin(FishType,QPointF)));
        connect(fish, SIGNAL(ImDied(FishModel*)), this, SLOT(fish_die(FishModel*)));
        addItem(fish);
        break;
    }
    case smallmomi:
    case moderatemomi:
    case bigmomi:
    {
        Momi* fish = new Momi(type, pos);
        connect(fish, SIGNAL(ImGrown(FishModel*)), this, SLOT(fishGrown(FishModel*)));
        connect(fish, SIGNAL(ImHungry(FishModel*)), this, SLOT(fish_hungry(FishModel*)));
        connect(fish, SIGNAL(ImGiven(FishType,QPointF)), this, SLOT(productCoin(FishType,QPointF)));
        connect(fish, SIGNAL(ImDied(FishModel*)), this, SLOT(fish_die(FishModel*)));
        addItem(fish);
        break;
    }
    case meatfish:
    {
        MeatFish* fish = new MeatFish(type, pos);
        connect(fish, SIGNAL(ImGrown(FishModel*)), this, SLOT(fishGrown(FishModel*)));
        connect(fish, SIGNAL(ImHungry(FishModel*)), this, SLOT(fish_hungry(FishModel*)));
        connect(fish, SIGNAL(ImGiven(FishType,QPointF)), this, SLOT(productCoin(FishType,QPointF)));
        connect(fish, SIGNAL(ImDied(FishModel*)), this, SLOT(fish_die(FishModel*)));
        addItem(fish);
        break;
    }
    case shark:
    {
        Shark *fish = new Shark(type, pos);
        connect(fish, SIGNAL(ImGrown(FishModel*)), this, SLOT(fishGrown(FishModel*)));
        connect(fish, SIGNAL(ImHungry(FishModel*)), this, SLOT(fish_hungry(FishModel*)));
        connect(fish, SIGNAL(ImGiven(FishType,QPointF)), this, SLOT(productCoin(FishType,QPointF)));
        connect(fish, SIGNAL(ImDied(FishModel*)), this, SLOT(fish_die(FishModel*)));
        addItem(fish);
        break;
    }
    default:
        break;
    }

}

void Mscene::fishGrown(FishModel *now)
{
    createNewFish(static_cast<FishType>(now->getType()+1), now->pos());
    removeItem(now);
}

void Mscene::createNewMoney(ItemType type, QPointF pos)
{
    Gold *money = new Gold(gold_num, pos, type);
    connect(money, SIGNAL(gold_changed()), this, SLOT(gold_changed()));
    connect(money, SIGNAL(ImPicked(Gold*)), this, SLOT(goldPicked(Gold*)));
    addItem(money);
}

void Mscene::createNewFood(QPointF pos)
{
    if (foodTotalNumber < foodTopNumber){
        foodTotalNumber++;
        FoodItem *food = new FoodItem(pos, quality);
        connect(food, SIGNAL(overFlow(FoodItem*)), this, SLOT(foodOverFlow(FoodItem*)));
        addItem(food);
    }
}

void Mscene::createNewPet(PetType type, QPointF pos)
{
    switch (type) {
    case snails:
    {
        Snails *pet = new Snails();
        connect(pet, SIGNAL(newTarget(PetModel*)), this,SLOT(PetAiming(PetModel*)));
        connect(pet, SIGNAL(ImGiven(PetType,QPointF)), this,SLOT(PetGiving(PetType, QPointF)));
        addItem(pet);
        break;
    }
    case mermaid:
    {
        Mermaid *pet = new Mermaid(mermaid, pos);
        connect(pet, SIGNAL(newTarget(PetModel*)), this,SLOT(PetAiming(PetModel*)));
        connect(pet, SIGNAL(ImGiven(PetType,QPointF)), this,SLOT(PetGiving(PetType, QPointF)));
        addItem(pet);
        break;
    }
    case dolphin:
    {
        Dolphin *pet = new Dolphin(dolphin, pos);
        connect(pet, SIGNAL(newTarget(PetModel*)), this,SLOT(PetAiming(PetModel*)));
        connect(pet, SIGNAL(ImGiven(PetType,QPointF)), this,SLOT(PetGiving(PetType, QPointF)));
        addItem(pet);
        break;
    }
    case bang:
    {
        Bang *pet = new Bang(bang, pos);
        connect(pet, SIGNAL(newTarget(PetModel*)), this,SLOT(PetAiming(PetModel*)));
        connect(pet, SIGNAL(ImGiven(PetType,QPointF)), this,SLOT(PetGiving(PetType, QPointF)));
        addItem(pet);
        break;
    }
    case feeder:
    {
        Feeder  *pet = new Feeder(feeder, pos);
        connect(pet, SIGNAL(newTarget(PetModel*)), this,SLOT(PetAiming(PetModel*)));
        connect(pet, SIGNAL(ImGiven(PetType,QPointF)), this,SLOT(PetGiving(PetType, QPointF)));
        addItem(pet);
        break;
    }
    case tuna:
    {
        Tuna  *pet = new Tuna(tuna, pos);
        connect(pet, SIGNAL(newTarget(PetModel*)), this,SLOT(PetAiming(PetModel*)));
        connect(pet, SIGNAL(ImGiven(PetType,QPointF)), this,SLOT(PetGiving(PetType, QPointF)));
        addItem(pet);
        break;
    }
    default:
        break;
    }
}

void Mscene::PetAiming(PetModel * now)
{
    bool isNull = true;
    switch (now->getPetType()) {
    case snails:
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == QGraphicsItem::UserType+14) {
                if (now->collidesWithItem(item)){
                    Gold *money = (Gold*)item;
                    money->pick_start();
                } else{
                    if (qrand()%4 == 0) now->setTarget(QPointF(item->scenePos().x(), 520));
                }
            }
        }
        break;
    case mermaid:
        if (qrand()%4 == 0) now->setTarget(QPointF(qrand()%900, qrand()%500));
        break;
    case dolphin:
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == QGraphicsItem::UserType+14) {
                isNull = false;
                if (now->collidesWithItem(item)){
                    Gold *money = (Gold*)item;
                    money->pick_start();
                } else{
                    if (qrand()%4 == 0) now->setTarget(item->scenePos());
                }
            }
        }
        if (isNull) now->setTarget(QPointF(qrand()%900, qrand()%500));
        break;
    case bang:
        break;
    case feeder:
    {
        Feeder* nowX = (Feeder*) now;
        if (nowX->getCondition()){
            foreach (QGraphicsItem *item, items()) {
                if (item->type() == QGraphicsItem::UserType+16) {
                    FishModel *fish = (FishModel*) item;
                    if (fish->getCondition() != hungry) continue;
                    if (now->collidesWithItem(item)){
                        fish->eat(nowX->hungry_function(), nowX->grown_function());
                        nowX->resetCondition();
                        break;
                    } else{
                        if (qrand()%2 == 0) {
                            now->setTarget(item->scenePos());
                            break;
                        }
                    }
                }
            }
        } else {
            nowX->setTarget(QPointF(qrand()%900, qrand()%500));
        }

        break;
    }
    case tuna:
    {
        Tuna *nowX = (Tuna*)now;
        if (monstercount == 0) {
            if (qrand()%2 == 0) break;
            if (nowX->getCondition()) nowX->resetCondition();
            nowX->setTarget(QPointF(qrand()%900, qrand()%500));
        } else{
            if (!nowX->getCondition()) nowX->setCondition();
            foreach (QGraphicsItem *item, items()) {
                if (item->type() == QGraphicsItem::UserType+19) {
                    AlienModel *enemy = (AlienModel*) item;
                    if (now->collidesWithItem(item)){
                        if (enemy->getType() != missile) enemy->eat(nowX->hungry_function());
                    } else{
                            QPointF tmp =  item->scenePos();
                            if (now->scenePos().x() < tmp.x()) {
                                if (now->scenePos().y() < tmp.y())
                                now->setTarget(QPointF(tmp.x()+100, tmp.y()+100));
                                else now->setTarget(QPointF(tmp.x()+100, tmp.y()-100));
                            } else{
                                if (now->scenePos().y() < tmp.y())
                                now->setTarget(QPointF(tmp.x()-100, tmp.y()+100));
                                else now->setTarget(QPointF(tmp.x()-100, tmp.y()-100));
                            }
                            break;
                    }
                }
            }
        }

        break;
    }
    default:
        break;
    }
}

void Mscene::PetGiving(PetType type, QPointF pos)
{
    switch (type){
    case snails:
    case dolphin:
    case feeder:
    case tuna:
        break;
    case mermaid:
        foreach (QGraphicsItem *item, items()) {
            if (item->type() == QGraphicsItem::UserType+16) {
               ((FishModel*)item)->ImGiving();
            }
        }
        break;
    case bang:
        createNewMoney(special, QPointF(108, 458));
        break;
    default:
        break;
    }
}

void Mscene::productCoin(FishType type, QPointF pos)
{
    switch (type) {
    case smallgubi:
    case smallmomi:
        break;
    case moderategubi:
        createNewMoney(small, pos);
        break;
    case biggubi:
        createNewMoney(moderate, pos);
        break;
    case kinggubi:
        createNewMoney(large, pos);
        break;
    case meatfish:
        createNewMoney(large, pos);
        break;
    case bigmomi:
    case moderatemomi:
        createNewFish(smallgubi, pos);
        break;
    case shark:
        createNewMoney(so_many, pos);
        break;
    default:
        break;
    }
}

void Mscene::ImMonster()
{
    if (attack_count<0) return;
    frame++;
    if (frame %18 == 0){
        emit MonsterBGM();
        attack_count++;
        return;
    }
    if (frame %19!=0){
        return;
    }

    int i=attack_count;
    if (i>3) i=3;
    while (i!=0){
        i--;

        AlienType type = monster;
        int judge = qrand()%7;
        if (judge == 0) continue;
        else if (judge >= 5) type = foodie;
        else if (judge == 4) type = destructor;
        else type = monster;
        monstercount++;

        switch (type) {
        case monster:
        {
            BlueMonster *alien = new BlueMonster();
            connect(alien, SIGNAL(ImDied(AlienModel*)), this, SLOT(MonsterDie(AlienModel*)));
            connect(alien, SIGNAL(newTarget(AlienModel*)), this, SLOT(MonsterAiming(AlienModel*)));
            addItem(alien);
            break;
         }
        case foodie:
        {
            Foodie *alien = new Foodie();
            connect(alien, SIGNAL(ImDied(AlienModel*)), this, SLOT(MonsterDie(AlienModel*)));
            connect(alien, SIGNAL(newTarget(AlienModel*)), this, SLOT(MonsterAiming(AlienModel*)));
            addItem(alien);
            break;
        }
        case destructor:
        {
            Destructor *alien = new Destructor();
            connect(alien, SIGNAL(ImDied(AlienModel*)), this, SLOT(MonsterDie(AlienModel*)));
            connect(alien, SIGNAL(newTarget(AlienModel*)), this, SLOT(MonsterAiming(AlienModel*)));
            connect(alien, SIGNAL(Rua(AlienModel*)), this, SLOT(MonsterRua(AlienModel*)));
            addItem(alien);
            createMissile(alien);
            break;
        }
        default:
            break;
        }
    }

    if (monstercount == 0) {
        emit FeedBGM();
        return;
    }

}

void Mscene::MonsterDie(AlienModel *now)
{
    int num=0;
    switch (now->getType()){
    case missile:
        num = 0;
        break;
    case monster:
        num = 1;
        break;
    case foodie:
        num = 2;
        break;
    case destructor:
        num = 3;
        break;
    case boss:
        num = 15;
        break;
    default :
        num = 2;
        break;
    }
    for (int i =0; i<num; i++)
        createNewMoney(large, QPointF(now->scenePos().x()-10+qrand()%20, now->scenePos().y()-10+qrand()%20));

    monstercount--;
    if (monstercount == 0) emit FeedBGM();
    removeItem(now);
}

void Mscene::MonsterAiming(AlienModel *now)
{
    bool isNull = true;
    switch (now->getType()) {
    case monster:
        foreach (QGraphicsItem *item, items()) {
            if (item->type() >= QGraphicsItem::UserType+16 && item->type() <= QGraphicsItem::UserType+18) {
                if (now->collidesWithItem(item)){
                    FishModel *food = (FishModel*)item;
                    food->attacked(0.7);
                } else{
                    now->setTarget(item->scenePos());
                }
            }
        }
        break;
    case foodie:
        foreach (QGraphicsItem *item, items()) {
            if (item->type() >= QGraphicsItem::UserType+15 && item->type() <= QGraphicsItem::UserType+18) {
                if (now->collidesWithItem(item)){
                    if (item->type() == QGraphicsItem::UserType+15){
                        FoodItem *food = (FoodItem*)item;
                        now->eat(food->hungry_function());
                        foodOverFlow(food);
                    } else{
                        FishModel *food = (FishModel*)item;
                        food->attacked(1);
                        now->eat(food->hungry_function()/2);
                    }
                } else{
                    now->setTarget(item->scenePos());
                }
            }
        }
        break;
    case destructor:
        if (qrand()%4 == 0) now->setTarget(QPointF(qrand()%900, 480));
        break;
    case missile:
        foreach (QGraphicsItem *item, items()) {
            if (item->type() >= QGraphicsItem::UserType+16 && item->type() <= QGraphicsItem::UserType+18) {
                isNull = false;
                if (now->collidesWithItem(item)){
                    FishModel *food = (FishModel*)item;
                    food->attacked(3);
                    now->eat(food->hungry_function());
                    break;
                } else{
                    now->setTarget(item->scenePos());
                    break;
                }
            }
        }
        if (isNull && qrand()%2 == 0) now->setTarget(QPointF(qrand()%900, qrand()%500));
        break;
    case boss:
        if (qrand()%3 == 0) now->setTarget(QPointF((qrand()%200) + 700, qrand()%500));
        break;
    default:
        break;
    }
}

void Mscene::MonsterRua(AlienModel *now)
{
    switch (now->getType()){
    case destructor:
        createMissile(now);
        break;
    case boss:
    {
        int num = qrand()%3;
        for (int i=0; i<num; i++){
            AlienType type = monster;
            int judge = qrand()%7;
            if (judge == 0) continue;
            else if (judge >= 5) type = foodie;
            else if (judge == 4) type = destructor;
            else type = monster;
            monstercount++;

            switch (type) {
            case monster:
            {
                BlueMonster *alien = new BlueMonster();
                connect(alien, SIGNAL(ImDied(AlienModel*)), this, SLOT(MonsterDie(AlienModel*)));
                connect(alien, SIGNAL(newTarget(AlienModel*)), this, SLOT(MonsterAiming(AlienModel*)));
                addItem(alien);
                break;
             }
            case foodie:
            {
                Foodie *alien = new Foodie();
                connect(alien, SIGNAL(ImDied(AlienModel*)), this, SLOT(MonsterDie(AlienModel*)));
                connect(alien, SIGNAL(newTarget(AlienModel*)), this, SLOT(MonsterAiming(AlienModel*)));
                addItem(alien);
                break;
            }
            case destructor:
            {
                Destructor *alien = new Destructor();
                connect(alien, SIGNAL(ImDied(AlienModel*)), this, SLOT(MonsterDie(AlienModel*)));
                connect(alien, SIGNAL(newTarget(AlienModel*)), this, SLOT(MonsterAiming(AlienModel*)));
                connect(alien, SIGNAL(Rua(AlienModel*)), this, SLOT(createMissile(AlienModel*)));
                addItem(alien);
                createMissile(alien);
                break;
            }
            default:
                break;
            }
        }

        break;
    }
    default:
        break;
    }
}

void Mscene::createMissile(AlienModel *now)
{
    for (int i=0; i<3;i++){
        monstercount++;
        Missile *attack = new Missile(now->scenePos());
        connect(attack, SIGNAL(ImDied(AlienModel*)), this, SLOT(MonsterDie(AlienModel*)));
        connect(attack, SIGNAL(newTarget(AlienModel*)), this, SLOT(MonsterAiming(AlienModel*)));
        addItem(attack);
    }

}

