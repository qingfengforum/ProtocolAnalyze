#-------------------------------------------------
#
# Project created by QtCreator 2017-07-23T22:42:35
#
#-------------------------------------------------

QT       += core gui
QT       += serialport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProtocolAnalyze
TEMPLATE = app


SOURCES += main.cpp\
        protocolanalyze.cpp \
    console.cpp \
    protocolgeneratordialog.cpp

HEADERS  += protocolanalyze.h \
    console.h \
    protocolgeneratordialog.h

FORMS    += protocolanalyze.ui \
    protocolgeneratordialog.ui

RC_ICONS = taylor.ico #add app icon
