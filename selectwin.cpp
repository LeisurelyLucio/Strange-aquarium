#include "selectwin.h"
#include "ui_selectwin.h"

selectWin::selectWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::selectWin)
{
    ui->setupUi(this);
    this->setWindowTitle("strange squarium");

    //通过styleSheet方法设置格式，添加类名标识防止对子类产生影响
    this->setStyleSheet(QString::fromUtf8("#selectWin{border-image: url(:/img/bkg/gaming.jpg)}"));
    ui->groupBox->setStyleSheet("#groupBox{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(195, 134, 243, 150), stop:1 rgba(255, 255, 255, 200))}");
    ui->groupBox_2->setStyleSheet("#groupBox_2{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(195, 134, 243, 150), stop:1 rgba(255, 255, 255, 200))}");

    //通过styleSheet方法设置格式，圆角矩形以及背景渐变
    ui->pushButton->setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;"
                                       "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(147, 49, 255, 255), stop:1 rgba(255, 255, 255, 255));"
                                        "font-family:'华文琥珀';font-size:13px");

    num = 0;
    pflag = NULL;

    m_pButtonGroup = new QButtonGroup(this);
    // 设置互斥
    m_pButtonGroup->setExclusive(true);
    m_pButtonGroup->addButton(ui->radioButton);
    m_pButtonGroup->addButton(ui->radioButton_2);
    m_pButtonGroup->addButton(ui->radioButton_3);
    m_pButtonGroup->addButton(ui->radioButton_4);
    connect(m_pButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonClicked(QAbstractButton*)));

    m_pButtonGroup2 = new QButtonGroup(this);
    m_pButtonGroup2->setExclusive(false);
    m_pButtonGroup2->addButton(ui->radioButton_5);
    m_pButtonGroup2->addButton(ui->radioButton_6);
    m_pButtonGroup2->addButton(ui->radioButton_7);
    m_pButtonGroup2->addButton(ui->radioButton_8);
    m_pButtonGroup2->addButton(ui->radioButton_9);
    m_pButtonGroup2->addButton(ui->radioButton_10);

    connect(m_pButtonGroup2, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(onButtonSelect(QAbstractButton*)));

}

selectWin::~selectWin()
{
    delete m_pButtonGroup;
    delete m_pButtonGroup2;
    delete ui;
}

void selectWin::onGameinit(int &initflag)
{
    int &flag = initflag;
    pflag = &initflag;
    ui->radioButton->setChecked(true);
    ui->radioButton_5->setChecked(true);
    flag = flag | 128 | 2;
    show();
}

void selectWin::onButtonClicked(QAbstractButton *now)
{
    int &flag = *pflag;

    if (now->text() == ui->radioButton->text())
    {
        flag = (flag | 128);
        if (flag & 256) flag = flag ^ 256;
        if (flag & 512) flag = flag ^ 512;
        if (flag & 1024) flag = flag ^ 1024;
    }
    else if (now->text() == ui->radioButton_2->text()){
        flag = (flag | 256);
        if (flag & 128) flag = flag ^ 128;
        if (flag & 512) flag = flag ^ 512;
        if (flag & 1024) flag = flag ^ 1024;
    }
    else if (now->text() ==  ui->radioButton_3->text()){
        flag = (flag | 512);
        if (flag & 128) flag = flag ^ 128;
        if (flag & 256) flag = flag ^ 256;
        if (flag & 1024) flag = flag ^ 1024;
    }
    else if (now->text() == ui->radioButton_4->text()){
        flag = (flag | 1024);
        if (flag & 128) flag = flag ^ 128;
        if (flag & 256) flag = flag ^ 256;
        if (flag & 512) flag = flag ^ 512;
        if (flag & 1024) flag = flag ^ 1024;
    }
}

void selectWin::onButtonSelect(QAbstractButton *now)
{
    int &flag = *pflag;
    // 遍历按钮，获取选中状态
    num = 0;
    QList<QAbstractButton*> list = m_pButtonGroup2->buttons();
    foreach (QAbstractButton *pButton, list)
    {
        if (pButton->isChecked()) {
            num++;
            if (num>3){
                num--;
                pButton->setChecked(false);
                if (pButton->text() == ui->radioButton_5->text())
                    if (flag & 2) flag = flag ^ 2;
                else if (pButton->text() == ui->radioButton_6->text())
                    if (flag & 16) flag = flag ^ 16;
                else if (pButton->text() == ui->radioButton_7->text())
                    if (flag & 8) flag = flag ^ 8;
                else if (pButton->text() == ui->radioButton_8->text())
                    if (flag & 64) flag = flag ^ 64;
                else if (pButton->text() == ui->radioButton_9->text())
                    if (flag & 32) flag = flag ^ 32;
                else if (pButton->text() == ui->radioButton_10->text())
                    if (flag & 4) flag = flag ^ 4;
                continue;
            }
            if (pButton->text() == ui->radioButton_5->text())
                flag = flag | 2;
            else if (pButton->text() == ui->radioButton_6->text())
                flag = flag | 16;
            else if (pButton->text() == ui->radioButton_7->text())
                flag = flag | 8;
            else if (pButton->text() == ui->radioButton_8->text())
                flag = flag | 64;
            else if (pButton->text() == ui->radioButton_9->text())
                flag = flag | 32;
            else if (pButton->text() == ui->radioButton_10->text())
                flag = flag | 4;
        } else {
            if (pButton->text() == ui->radioButton_5->text())
                if (flag & 2) flag = flag ^ 2;
            else if (pButton->text() == ui->radioButton_6->text())
                if (flag & 16) flag = flag ^ 16;
            else if (pButton->text() == ui->radioButton_7->text())
                if (flag & 8) flag = flag ^ 8;
            else if (pButton->text() == ui->radioButton_8->text())
                if (flag & 64) flag = flag ^ 64;
            else if (pButton->text() == ui->radioButton_9->text())
                if (flag & 32) flag = flag ^ 32;
            else if (pButton->text() == ui->radioButton_10->text())
                if (flag & 4) flag = flag ^ 4;
        }
    }


}

void selectWin::on_pushButton_clicked()
{
    emit start();

    close();
}
