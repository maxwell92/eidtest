#-------------------------------------------------
#
# Project created by QtCreator 2014-12-15T15:36:51
#
#-------------------------------------------------

QT       += core gui
QT       += network\
         sql

TARGET = eidServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    citizen.cpp

HEADERS  += mainwindow.h \
    citizen.h

FORMS    += mainwindow.ui
