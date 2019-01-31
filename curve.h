#ifndef CURVE_H
#define CURVE_H

#include <QWidget>
#include <QTimer>
#include <QList>
#include <QPainter>
#include <QPointF>
#include <QPen>
#include <qmath.h>
class Curve : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *);

public:
    int m_count;
    float x;
    QTimer* m_Timer;
    QList<float> xList;
    QList<float> yList;

    explicit Curve(QWidget *parent = 0);
    ~Curve();

signals:

public slots:

    void creatData();

};

#endif // CURVE_H
