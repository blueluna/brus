#-------------------------------------------------
#
# Project created by QtCreator 2014-09-13T23:54:16
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = brus
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp\
        src/classicnoise.cpp \
    src/simplexnoise.cpp \
    src/openglwidget.cpp

INCLUDEPATH += $$PWD/include
HEADERS += include/mainwindow.h include/classicnoise.h \
    include/simplexnoise.h \
    include/openglwidget.h \
    include/primitives.h

FORMS += ui/mainwindow.ui

RESOURCES += \
    resources.qrc
