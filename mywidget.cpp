#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::MyWidget)
{

    ui->setupUi(this);
    resize(1200,800);
//    ui->pushButton->setGeometry(560,120,80,30);
    //home title
    ui->label->setStyleSheet("QLabel{color:rgb(255,255,255);"
                               "background-color:rgb(111,123,242);"
                             "}");

    // display the current time!

    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));

    //set the Style of realDataBtn
    ui->realDataBtn->setStyleSheet("QPushButton{color:rgb(255,255,255);"
                               "background-color:rgb(50,205,50);"
                             "}");

//    QPainter p(ui->realDataBtn);
//    p.drawPixmap(rect(),QPixmap("../images/datasheet.jpg"));
    QIcon icon;
    icon.addFile(tr("../images/datasheet.jpg"));
    //ui->realDataBtn->setStyleSheet("background-image:url(../images/datasheet.png)");
    ui->realDataBtn->setIcon(icon);
    /*
    **set the bakpicture
    */
    QImage imagel;
    QPalette palette;
    imagel.load(":/img/123.jpg");
    //imagel.load("/home/linux/qt_file/Xiangmu/jiajubeijing1.jpg");
    palette.setBrush(this->backgroundRole(),QBrush(imagel));
    this->setPalette(palette);

    real_data = new RealData();

    /**
     * the button of close!*/
    b1.setParent(this);
    QIcon bicon(":/img/close.jpg");
    b1.setIcon(bicon);
    b1.move(1100,10);
    b1.setFlat(true);//扁平化
    connect(&b1,&QPushButton::clicked,this,&MyWidget::close);


}
void MyWidget::closeEvent(QCloseEvent *e)
{
    int ret = QMessageBox::question(this,"关闭","确认退出系统？");
    if(ret==QMessageBox::Yes)
    {
        e->accept();
          qDebug()<<"enen11";//打印，提示关闭事件已经被选择了
    }
    else
    {
        e->ignore();
          qDebug()<<"enen22";//打印，提示关闭事件已经被选择了

    }
}

void MyWidget::timerUpDate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString curtime = time.toString("20yy-MM-dd hh:mm:ss dddd");
    QFont ft;
    ft.setPointSize(20);
    ui->timeLabel->setText(curtime);
    ui->timeLabel->setStyleSheet("QLabel{color:rgb(255,255,255);"
                                 "background-color:rgb(111,123,242);"
                               "}");
    ui->timeLabel->setFont(ft);

//    ui->timeLabel->adjustSize();
}

MyWidget::~MyWidget()
{
    delete ui;
}


void MyWidget::on_realDataBtn_clicked()
{
//    this->hide();
    real_data->show();
}

void MyWidget::on_pushButton_clicked()
{
    this->hide();

}
