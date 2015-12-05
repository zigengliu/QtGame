#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T13:19:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hw4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gameboard.cpp

HEADERS  += mainwindow.h \
    gameboard.h

FORMS    += mainwindow.ui \
    gameboard.ui

RESOURCES += \
    image.qrc

DISTFILES += \
    instr.txt
