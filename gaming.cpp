#include "gaming.h"
#include "ui_gaming.h"

Gaming::Gaming(QMediaPlayer &mus, QMediaPlaylist &mlist, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gaming),
    music(&mus),
    playlist(&mlist)
{
    ui->setupUi(this);

    this->setWindowTitle("strange squarium");

    //通过styleSheet方法设置格式，添加类名标识防止对子类产生影响
    this->setStyleSheet(QString::fromUtf8("#Gaming{border-image: url(:/img/bkg/gaming.jpg)}"));
    ui->groupBox->setStyleSheet("#groupBox{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(195, 134, 243, 150), stop:1 rgba(255, 255, 255, 200))}");

    //通过styleSheet方法设置格式，圆角矩形以及背景渐变
    ui->pushButton_Back->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;"
                                       "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(147, 49, 255, 255), stop:1 rgba(255, 255, 255, 255));");

}

Gaming::~Gaming()
{
    delete ui;
    if (game_scene!=NULL) game_scene->clear();
    delete game_scene;
    game_scene = NULL;
}

void Gaming::on_pushButton_Back_clicked()
{        
    if (game_scene!=NULL) game_scene->clear();
    delete game_scene;
    game_scene = NULL;
    music->stop();

    emit ExitWin();
    close();


}

void Gaming::Sgame_start()
{  
    if (flag &128) gold_target = 500;
    else if (flag &256) gold_target = 3000;
    else if (flag &512) gold_target = 9000;
    else if (flag &1024) gold_target = 12000;
    else gold_target = 8000;

    gold = 200;
    ui->label_gold->setNum(gold);
    ui->label_Mtarget->setNum(gold_target);
    aiming = 3;
    ui->label_aim->setNum(aiming);
    game_scene = new Mscene(gold, QRectF(0, 0, 970, 530), flag);
    gameSceneInit();

    show();

    playFeedBGM();

}

void Gaming::Sgame_init()
{
    flag = 0;
    emit selectNow(flag);
}

void Gaming::Bgame_start()
{
    gold = 5000;
    gold_target = 9000;
    ui->label_gold->setNum(gold);
    ui->label_Mtarget->setNum(gold_target);
    aiming = 3;
    ui->label_aim->setNum(aiming);
    game_scene = new Mscene(gold, QRectF(0, 0, 970, 530), 1);
    gameSceneInit();

    show();

    playBossBGM();
}

void Gaming::gold_changed()
{
    ui->label_gold->setNum(gold);
}

void Gaming::playMonsterBGM()
{
    playlist->setCurrentIndex(2);
    music->play();
}

void Gaming::playFeedBGM()
{
    playlist->setCurrentIndex(1);
    music->play();
}

void Gaming::playBossBGM()
{
    playlist->setCurrentIndex(3);
    music->play();
}

void Gaming::gameSceneInit()
{
    ui->gameView->setRenderHint(QPainter::Antialiasing);
    ui->gameView->setScene(game_scene);    

    connect(game_scene, SIGNAL(goldChanged()), this, SLOT(gold_changed()));
    connect(this, SIGNAL(FoodNumUp()), game_scene, SLOT(foodNum_changed()));
    connect(this, SIGNAL(FoodQualityUp()), game_scene, SLOT(foodQuality_changed()));
    connect(game_scene, SIGNAL(FeedBGM()), this, SLOT(playFeedBGM()));
    connect(game_scene, SIGNAL(MonsterBGM()), this, SLOT(playMonsterBGM()));
    connect(game_scene, SIGNAL(BossBGM()), this, SLOT(playBossBGM()));
}

void Gaming::on_pushButton_QUpdate_clicked()
{
    if (gold >= 300){
        if (game_scene!=NULL){
            if (game_scene->GetQuality()< so_many){
                gold-=300;
                emit FoodQualityUp();
                gold_changed();
            }
        }
    }
}

void Gaming::on_pushButton_NUpdate_clicked()
{
    if (gold >= 300){
        gold-=300;
        emit FoodNumUp();
        gold_changed();
    }
}

void Gaming::on_pushButton_Target_clicked()
{
    if (gold >= gold_target){
        gold-=gold_target;
        gold_changed();

        aiming--;
        ui->label_aim->setNum(aiming);
        if (aiming == 0){
            QMessageBox win(QMessageBox::NoIcon, QString("Win!!"), QString("你获得了胜利！"));
            win.exec();

            on_pushButton_Back_clicked();
        }
    }
}

void Gaming::on_pushButton_Gubi_clicked()
{
    if (gold >= 100){
        gold-=100;
        gold_changed();

        QPointF pos;
        pos.setX((qrand()%200)+400);
        pos.setY((qrand()%200)+200);
        game_scene->createNewFish(smallgubi, pos);
    }
}

void Gaming::on_pushButton_Momi_clicked()
{
    if (gold >= 200){
        gold-=200;
        gold_changed();

        QPointF pos;
        pos.setX((qrand()%200)+400);
        pos.setY((qrand()%200)+200);
        game_scene->createNewFish(smallmomi, pos);
    }
}

void Gaming::on_pushButton_meat_clicked()
{
    if (gold >= 1000){
        gold-=1000;
        gold_changed();

        QPointF pos;
        pos.setX((qrand()%200)+400);
        pos.setY((qrand()%200)+200);
        game_scene->createNewFish(meatfish, pos);
    }
}

void Gaming::on_pushButton_Bmeat_clicked()
{
    if (gold >= 10000){
        gold-=10000;
        gold_changed();

        QPointF pos;
        pos.setX((qrand()%200)+400);
        pos.setY((qrand()%200)+200);
        game_scene->createNewFish(shark, pos);
    }
}
