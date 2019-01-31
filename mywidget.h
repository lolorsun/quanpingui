#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "basewidget.h"
#include <QImage>
#include <QPalette>
#include <QPushButton>
#include <QIcon>
#include <QEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QFont>
#include <QPainter>
#include <QPixmap>
#include "realdata.h"
namespace Ui {
class MyWidget;
}

class MyWidget : public BaseWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private slots:
    void timerUpDate();


    void on_realDataBtn_clicked();

    void on_pushButton_clicked();

protected:
    void closeEvent(QCloseEvent *e);

private:
    Ui::MyWidget *ui;
    QPushButton b1;
    RealData *real_data;
};


#endif // MYWIDGET_H
