#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T21:21:25
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TiledGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tmxfiles.cpp

HEADERS  += mainwindow.h \
    tmxfiles.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 
