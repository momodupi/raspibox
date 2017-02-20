#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T17:13:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = raspberry
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clockwidget.cpp

HEADERS  += mainwindow.h \
    clockwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc

DISTFILES +=
