#-------------------------------------------------
#
# Project created by QtCreator 2014-09-13T23:54:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = brus
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp\
        src/classicnoise.cpp

INCLUDEPATH += $$PWD/include
HEADERS += include/mainwindow.h include/classicnoise.h

FORMS += ui/mainwindow.ui
