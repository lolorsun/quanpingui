#-------------------------------------------------
#
# Project created by QtCreator 2019-01-17T10:20:22
#
#-------------------------------------------------

QT       += core gui sql
QT       += widgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quanpingui
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    basewidget.cpp \
    realdata.cpp \
    curve.cpp \
    qcustomplot.cpp

HEADERS  += mywidget.h \
    basewidget.h \
    realdata.h \
    curve.h \
    qcustomplot.h \
    qcustomplot.h

FORMS    += mywidget.ui \
    realdata.ui

RESOURCES += \
    src.qrc
