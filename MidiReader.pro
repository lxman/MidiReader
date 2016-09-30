#-------------------------------------------------
#
# Project created by QtCreator 2016-09-25T01:39:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MidiReader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    headerchunk.cpp \
    ba32tobe.cpp \
    ba16tobe.cpp \
    trkchunk.cpp \
    vlqscanner.cpp \
    event.cpp

HEADERS  += mainwindow.h \
    headerchunk.h \
    ba32tobe.h \
    ba16tobe.h \
    trkchunk.h \
    globals.h \
    vlqscanner.h \
    event.h

FORMS    += mainwindow.ui
