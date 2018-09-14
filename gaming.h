#ifndef GAMING_H
#define GAMING_H

#include <QMainWindow>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMessageBox>
#include "mscene.h"

namespace Ui {
class Gaming;
}

class Gaming : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gaming(QMediaPlayer &mus, QMediaPlaylist &mlist, QWidget *parent = 0);
    ~Gaming();

private slots:
    void on_pushButton_Back_clicked();
    void Sgame_start();  //游戏初始化函数
    void Sgame_init();  //游戏初始化函数
    void Bgame_start();  //游戏初始化函数
    void gold_changed();
    void playMonsterBGM();
    void playFeedBGM();
    void playBossBGM();

    void on_pushButton_QUpdate_clicked();
    void on_pushButton_NUpdate_clicked();
    void on_pushButton_Target_clicked();
    void on_pushButton_Gubi_clicked();
    void on_pushButton_Momi_clicked();
    void on_pushButton_meat_clicked();
    void on_pushButton_Bmeat_clicked();

private:
    Ui::Gaming *ui;
    QMediaPlayer *music;
    QMediaPlaylist *playlist;
    Mscene *game_scene;
    int gold;
    int gold_target;
    int aiming;
    int flag;

   void gameSceneInit();  //初始化视图相关的操作

signals:
    void ExitWin();
    void FoodQualityUp();
    void FoodNumUp();
    void selectNow(int&);
};

#endif // GAMING_H
