#-------------------------------------------------
#
# Project created by QtCreator 2014-12-01T19:35:43
#
#-------------------------------------------------

QT       += core gui
QT       += network \
         sql
TARGET = SP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    reg.cpp \
    logger.cpp

HEADERS  += mainwindow.h \
    reg.h \
    logger.h

FORMS    += \
    mainwindow.ui
