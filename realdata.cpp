#include "realdata.h"
#include "ui_realdata.h"

RealData::RealData(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::RealData)
{
    ui->setupUi(this);
    resize(1280,800);
    this->move(0,0);
    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTimer()));

    //关闭按钮个性化设置
    b1.setParent(this);
    QIcon bicon(":/img/close.jpg");
    b1.setIcon(bicon);
    b1.move(1100,10);
    b1.setFlat(true);//扁平化
    //关闭实时数据界面
    connect(&b1,&QPushButton::clicked,this,&RealData::on_realdataBackHome_clicked);
    on_ButtonCurve_clicked();
    //设置实时数据样式
    ui->dataLabel->setStyleSheet("QLabel{color:rgb(255,255,0);"
                                 "backgroung-color:rgb(255,255,0)"
                                 "}");

}

RealData::~RealData()
{
    delete ui;
}
void RealData::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/img/123.jpg"));
}

//显示系统时间
void RealData::updateTimer()
{
    QDateTime time = QDateTime::currentDateTime();
    QString currentTime = time.toString("20yy-MM-dd hh:mm:ss");
    ui->timeLabel->setText(currentTime);
    QFont ft;
    ft.setPixelSize(25);

    ui->timeLabel->setFont(ft);

}

//点击显示实时曲线
void RealData::on_ButtonCurve_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageCurve);
    Curve *cur = new Curve();
    cur->setParent(ui->pageCurve);
//    cur->resize(600,600);
    cur->show();
}

//点击显示实时数据
void RealData::on_ButtonData_clicked()
{

//    ui->ButtonData->setEnabled(true);
    ui->stackedWidget->setCurrentWidget(ui->pageData);
    QPushButton *b = new QPushButton();
    b->setParent(ui->pageData);
    b->show();
    setupRealtimeDataDemo(ui->pageData);
    ui->pageData->replot();
//    ui->ButtonData->setEnabled(false);
//    ui->checkBox_temp->setChecked(true);
//    ui->checkBox_hui->setChecked(true);
}

void RealData::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setName("temp");
    //customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    //customPlot->graph(0)->setAntialiasedFill(false);
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(Qt::red));
    customPlot->graph(1)->setName("hui");
    //customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));


    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setTickStep(2);
//    customPlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    //connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    //connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(1000); // Interval 0 means to refresh as fast as possible
    customPlot->legend->setVisible(false);//设置false后，不显示曲线图列选择框提示信息

}

void RealData::realtimeDataSlot()
{
    //key的单位是秒
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    qsrand(QTime::currentTime().msec() + QTime::currentTime().second() * 10000);
    //使用随机数产生两条曲线
    double value0 = qrand() % 100;
    double value1 = qrand() % 80;
    if (ui->checkBox_temp->isChecked())
        ui->pageData->graph(0)->addData(key, value0);//添加数据1到曲线1
    if (ui->checkBox_hui->isChecked())
        ui->pageData->graph(1)->addData(key, value1);//添加数据2到曲线2
    //删除8秒之前的数据。这里的8要和下面设置横坐标宽度的8配合起来
    //才能起到想要的效果，可以调整这两个值，观察显示的效果。
    ui->pageData->graph(0)->removeDataBefore(key-8);
    ui->pageData->graph(1)->removeDataBefore(key-8);

      //自动设定graph(1)曲线y轴的范围，如果不设定，有可能看不到图像
//也可以用ui->customPlot->yAxis->setRange(up,low)手动设定y轴范围
    ui->pageData->graph(0)->rescaleValueAxis(true);
    ui->pageData->graph(1)->rescaleValueAxis(true);

    //这里的8，是指横坐标时间宽度为8秒，如果想要横坐标显示更多的时间
    //就把8调整为比较大到值，比如要显示60秒，那就改成60。
    //这时removeDataBefore(key-8)中的8也要改成60，否则曲线显示不完整。
    ui->pageData->xAxis->setRange(key+0.25, 8, Qt::AlignRight);//设定x轴的范围
    ui->pageData->replot();
}

//返回主界面漕函数
void RealData::on_realdataBackHome_clicked()
{
    emit bak_home();
}
