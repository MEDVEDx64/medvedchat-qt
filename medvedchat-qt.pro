#-------------------------------------------------
#
# Project created by QtCreator 2017-08-10T09:44:29
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = medvedchat-qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    protocol.cpp \
    value.cpp

HEADERS  += mainwindow.h \
    client.h \
    protocol.h \
    value.h \
    style.h
