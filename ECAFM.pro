#-------------------------------------------------
#
# Project created by QtCreator 2015-12-28T00:10:40
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ECAFM
TEMPLATE = app
CONFIG += c++14


SOURCES += main.cpp\
        mainwindow.cpp \
    soundplayer.cpp \
    waveform.cpp \
    utils.cpp \
    ElementaryCA.cpp

HEADERS  += mainwindow.h \
    soundplayer.h \
    utils.h \
    waveform.h \
    ElementaryCA.h

FORMS    += mainwindow.ui
