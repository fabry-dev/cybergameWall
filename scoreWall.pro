#-------------------------------------------------
#
# Project created by QtCreator 2018-09-10T15:05:51
#
#-------------------------------------------------

QT       += core gui network
CONFIG += c++14


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scoreWall
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scorewall.cpp

HEADERS  += mainwindow.h \
    scorewall.h

FORMS    += mainwindow.ui
