TEMPLATE = app

CONFIG += c++14
QMAKE_CXXFLAGS_CXX11    = -std=c++1y

QT += qml quick widgets
QT += serialport

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

#HEADERS +=


INCLUDEPATH += $$PWD/../alkfejl_hakLib

LIBS += -L$$OUT_PWD/../alkfejl_hakLib/ -lalkfejl_hakLib

# win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../alkfejl_hakLib/release/ -lalkfejl_hakLib
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../alkfejl_hakLib/debug/ -lalkfejl_hakLib
