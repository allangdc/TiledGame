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
    tmxfiles.cpp \
    tmxscreen.cpp

HEADERS  += \
    tmxfiles.h \
    tmxscreen.h

FORMS    +=

CONFIG += mobility
MOBILITY = 

