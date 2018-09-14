#ifndef STRANGE_SQUARIUM_H
#define STRANGE_SQUARIUM_H

#include <QMainWindow>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileInfo>
#include "gaming.h"

namespace Ui {
class Strange_Squarium;
}

class Strange_Squarium : public QMainWindow
{
    Q_OBJECT

public:
    explicit Strange_Squarium( QMediaPlayer &mus, QMediaPlaylist &mlist, QWidget *parent = 0);
    ~Strange_Squarium();

private slots:
    void on_PushButton_Quit_clicked();
    void on_PushButton_Venture_clicked();
    void on_pushButton_clicked();
    void On_show();//重新显示
    void on_PushButton_Shop_clicked();
    void on_PushButton_Boss_clicked();

private:
    Ui::Strange_Squarium *ui;
    QMediaPlayer *music;
    QMediaPlaylist *playlist;

signals:
    void Sgame_start();  //窗口切换信号
    void Bgame_start();  //窗口切换信号

};

#endif // STRANGE_SQUARIUM_H
