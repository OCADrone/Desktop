#-------------------------------------------------
#
# Project created by QtCreator 2013-09-29T06:53:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET =    OCADrone_Desktop

TEMPLATE =  app

CONFIG +=   static

SOURCES +=  main.cpp \
            mainwindow.cpp \
            module.cpp \
            modulehandler.cpp

HEADERS  += mainwindow.h \
            module.h \
            modulehandler.h

FORMS    += mainwindow.ui

# Windows

win32: INCLUDEPATH += include/windows

# Linux

unix: INCLUDEPATH += include/linux
unix: LIBS += -ldl

RESOURCES += \
             assets.qrc
