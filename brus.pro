#-------------------------------------------------
#
# Project created by QtCreator 2014-09-13T23:54:16
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = brus
TEMPLATE = app

QMAKE_MAC_SDK = macosx10.9

SOURCES += src/main.cpp\
        src/mainwindow.cpp\
        src/classicnoise.cpp \
    src/simplexnoise.cpp \
    src/openglwidget.cpp \
    src/TMatrix.cpp \
    src/TPoint.cpp \
    src/TVertex.cpp \
    src/T3DObject.cpp \
    src/TCube.cpp

INCLUDEPATH += $$PWD/include
HEADERS += include/mainwindow.h include/classicnoise.h \
    include/simplexnoise.h \
    include/openglwidget.h \
    include/TMatrix.h \
    include/OpenGl.h \
    include/TPoint.h \
    include/TVertex.h \
    include/T3DObject.h \
    include/MathConstants.h \
    include/TCube.h \
    include/TBox.h

FORMS += ui/mainwindow.ui

RESOURCES += \
    resources.qrc
