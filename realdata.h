#ifndef REALDATA_H
#define REALDATA_H

#include "basewidget.h"
#include <QPainter>
#include <QPushButton>
#include <QIcon>
#include <QTimer>
#include <QDateTime>

#include <QVector>
#include <QTime>

#include <QSqlQuery>
#include <QSqlDatabase>
#include "curve.h"
#include "qcustomplot.h"
namespace Ui {
class RealData;
}

class RealData : public BaseWidget
{
    Q_OBJECT

public:
    explicit RealData(QWidget *parent = 0);
    ~RealData();
    //设置qcustomplot画图属性，实时
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
signals:
    void bak_home(void);
private slots:
    void updateTimer();
    void on_ButtonCurve_clicked();//容器曲线页面切换

    void on_ButtonData_clicked();//容器实时页面切换
    //添加实时数据槽
    void realtimeDataSlot();
    void on_realdataBackHome_clicked();//返回主界面

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::RealData *ui;
    QPushButton b1;
    //定时器，周期调用realtimeDataSlot()槽，实现动态数据添加到曲线
    QTimer dataTimer;

};

#endif // REALDATA_H
