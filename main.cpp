#include "strange_squarium.h"
#include "gaming.h"
#include "selectwin.h"
#include <QApplication>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/img/bkg/start.png");
    QSplashScreen splash(pixmap);
    splash.setDisabled(true); //禁用用户的输入事件响应
    splash.show();

    //初始化与加载

    //音乐初始化时一定用audition消除附加信息！
    splash.showMessage(QObject::tr("正在初始化音乐文件...."),Qt::AlignLeft|Qt::AlignBottom,Qt::green);
    QMediaPlayer music;
    QMediaPlaylist playlist;
    QString Mstart = (QFileInfo("music/GoodNight.mp3").absoluteFilePath());
    QString Mgame = (QFileInfo("music/mountain.mp3").absoluteFilePath());
    QString Malien = (QFileInfo("music/LifeChange.mp3").absoluteFilePath());
    QString Mboss = (QFileInfo("music/fight.mp3").absoluteFilePath());
    playlist.addMedia(QUrl::fromLocalFile(Mstart));
    playlist.addMedia(QUrl::fromLocalFile(Mgame));
    playlist.addMedia(QUrl::fromLocalFile(Malien));
    playlist.addMedia(QUrl::fromLocalFile(Mboss));
    playlist.setCurrentIndex(0);
    playlist.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    music.setPlaylist(&playlist);

    music.play();

    //窗口初始化
    splash.showMessage(QObject::tr("正在初始化窗口...."),Qt::AlignLeft|Qt::AlignBottom,Qt::green);
    Gaming initialG(music, playlist);
    initialG.setWindowFlags(initialG.windowFlags()& ~Qt::WindowMaximizeButtonHint & ~Qt::WindowCloseButtonHint);
    Strange_Squarium w(music, playlist);
    w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint & ~Qt::WindowCloseButtonHint);
    selectWin s;
    s.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint & ~Qt::WindowCloseButtonHint);
    a.connect(&w, SIGNAL(Sgame_start()), &initialG, SLOT(Sgame_init()));
    a.connect(&w, SIGNAL(Bgame_start()), &initialG, SLOT(Bgame_start()));
    a.connect(&initialG, SIGNAL(selectNow(int&)), &s, SLOT(onGameinit(int&)));
    a.connect(&s, SIGNAL(start()), &initialG, SLOT(Sgame_start()));
    a.connect(&initialG, SIGNAL(ExitWin()), &w, SLOT(On_show()));

    //空循环1s
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<1000) {}

    w.show();
    splash.finish(&w);

    return a.exec();
}
