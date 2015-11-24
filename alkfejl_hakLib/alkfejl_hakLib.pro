#-------------------------------------------------
#
# Project created by QtCreator 2015-11-21T22:08:42
#
#-------------------------------------------------


QT       -= gui

TARGET = alkfejl_hakLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += alkfejl_haklib.cpp

HEADERS += alkfejl_haklib.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
