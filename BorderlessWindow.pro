#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T22:49:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BorderlessWindow
TEMPLATE = app


SOURCES += main.cpp\
        borderlesswindow.cpp \
    ltitlebar.cpp \
    lnativeeventfilter.cpp \
    lmsghandler.cpp

HEADERS  += borderlesswindow.h \
    ltitlebar.h \
    lnativeeventfilter.h \
    lmsghandler.h

FORMS    += borderlesswindow.ui \
    ltitlebar.ui

RESOURCES += \
    resource.qrc
