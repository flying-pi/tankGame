QT += core  gui network concurrent

CONFIG += c++14

TARGET = Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_LFLAGS += -rdynamic

SOURCES += main.cpp \
    maingameloop.cpp \
    mapiniter.cpp \
    serverconnection.cpp \
    serverworker.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

RESOURCES +=

HEADERS += \
    maingameloop.h \
    mapiniter.h \
    const.h \
    serverconnection.h \
    serverworker.h


