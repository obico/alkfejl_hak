QT += core testlib
QT -= gui

TARGET = alkfejl_hakTest
CONFIG += console
CONFIG -= app_bundle
CONFIG += testcase

TEMPLATE = app

SOURCES += main.cpp \
    alkfejl_hakapplicationtest.cpp

HEADERS += \
    alkfejl_hakapplicationtest.h
