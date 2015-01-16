QT          += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE =  lib

# CONFIG += staticlib

DEFINES     += \
            MODULE_NAME

HEADERS     += \
            widget.h \
            localsocketipcclient.h \
            mymodule.h

SOURCES     += \
            widget.cpp \
            localsocketipcclient.cpp \
            mymodule.cpp

FORMS       += \
            Form.ui
