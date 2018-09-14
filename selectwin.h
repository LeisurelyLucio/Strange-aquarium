#ifndef SELECTWIN_H
#define SELECTWIN_H

#include <QMainWindow>
#include <QButtonGroup>

namespace Ui {
class selectWin;
}

class selectWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit selectWin(QWidget *parent = 0);
    ~selectWin();
private:
    Ui::selectWin *ui;
    int *pflag;
    QButtonGroup *m_pButtonGroup, *m_pButtonGroup2;
    int num;

 signals:
    void start();

protected slots:
    void onGameinit(int &);
    void onButtonClicked(QAbstractButton*);
    void onButtonSelect(QAbstractButton*);


private slots:
    void on_pushButton_clicked();
};

#endif // SELECTWIN_H
