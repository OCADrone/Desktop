#-------------------------------------------------
#
# Project created by QtCreator 2003-01-17T14:33:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XMLCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlmanager.cpp

HEADERS  += mainwindow.h \
    xmlmanager.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

