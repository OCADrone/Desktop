QT          += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE =  lib

# CONFIG += staticlib

DEFINES     += \
            MODULE_NAME

HEADERS     += \
            widget.h \
            mymodule.h

SOURCES     += \
            widget.cpp \
            mymodule.cpp

FORMS       += \
            Form.ui
