#-------------------------------------------------
#
# Project created by QtCreator 2016-05-27T13:43:48
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-2D-viewer
TEMPLATE = app

LIBS += opengl32.lib glut32.lib glut.lib

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp

HEADERS  += mainwindow.h \
    glwidget.h

FORMS    += mainwindow.ui
