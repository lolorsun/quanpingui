#include "mywidget.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();
    qDebug()<<"hello";

    return a.exec();
}
