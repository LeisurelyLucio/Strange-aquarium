#include "strange_squarium.h"
#include "ui_strange_squarium.h"


Strange_Squarium::Strange_Squarium(QMediaPlayer &mus, QMediaPlaylist &mlist, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Strange_Squarium),
    music(&mus),
    playlist(&mlist)
{
    ui->setupUi(this);

    this->setWindowTitle("strange squarium");

    //通过styleSheet方法设置格式，添加类名标识防止对子类产生影响
    this->setStyleSheet(QString::fromUtf8("#Strange_Squarium{border-image: url(:/img/bkg/start_Stage.jpg)}"));

    //通过styleSheet方法设置格式，圆角矩形以及背景渐变
    ui->groupBox_Start->setStyleSheet("border:3px groove gray;border-radius:20px;padding:2px 4px;"
                                      "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(82, 91, 224, 100), stop:1 rgba(255, 255, 255, 130));");

    ui->PushButton_Quit->setStyleSheet("border:2px groove gray;border-radius:20px;padding:2px 4px;"
                                       "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(147, 49, 255, 255), stop:1 rgba(255, 255, 255, 255));");
    ui->PushButton_Venture->setStyleSheet("border:2px groove gray;border-radius:20px;padding:2px 4px;"
                                       "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(147, 49, 255, 255), stop:1 rgba(255, 255, 255, 255));");
    ui->PushButton_Shop->setStyleSheet("border:2px groove gray;border-radius:20px;padding:2px 4px;"
                                       "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(147, 49, 255, 255), stop:1 rgba(255, 255, 255, 255));");
    ui->PushButton_Boss->setStyleSheet("border:2px groove gray;border-radius:20px;padding:2px 4px;"
                                       "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(147, 49, 255, 255), stop:1 rgba(255, 255, 255, 255));");

    ui->label->setStyleSheet("color:rgb(170,192,255)");
    ui->label_2->setStyleSheet("color:rgb(170,192,255)");

}

Strange_Squarium::~Strange_Squarium()
{
    delete ui;
    delete music;
}

void Strange_Squarium::on_PushButton_Quit_clicked()
{
    exit(0);
}

void Strange_Squarium::on_PushButton_Venture_clicked()
{
    this->close();
    music->stop();
    emit Sgame_start();
}

void Strange_Squarium::on_pushButton_clicked()
{
    music->stop();
    playlist->setCurrentIndex((playlist->currentIndex()+1)%playlist->mediaCount());
    music->play();
}

void Strange_Squarium::On_show()
{
    show();
    playlist->setCurrentIndex(0);
    music->play();
}

void Strange_Squarium::on_PushButton_Shop_clicked()
{
    QMessageBox win(QMessageBox::NoIcon, QString("wait!!"), QString("暂无此功能！"));
    win.exec();
}

void Strange_Squarium::on_PushButton_Boss_clicked()
{
    this->close();
    music->stop();
    emit Bgame_start();
}
