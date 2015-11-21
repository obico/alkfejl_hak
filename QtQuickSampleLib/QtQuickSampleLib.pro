#-------------------------------------------------
#
# Project created by QtCreator 2015-11-21T22:05:58
#
#-------------------------------------------------

QT       -= gui

TARGET = QtQuickSampleLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES +=

HEADERS +=
unix {
    target.path = /usr/lib
    INSTALLS += target
}
