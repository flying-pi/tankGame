#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T13:17:33
#
#-------------------------------------------------

QT       -= gui

QT += core  gui network concurrent


TARGET = Core
TEMPLATE = lib

QMAKE_LFLAGS += -rdynamic

CONFIG += c++14

DEFINES += CORE_LIBRARY

SOURCES += core.cpp \
    infinitydouble.cpp \
    imap.cpp \
    ibasegameelement.cpp \
    maps/listbsemap.cpp \
    connection/simpleconnection.cpp \
    GameElements/basetank.cpp \
    GameElements/basebulet.cpp

HEADERS += core.h\
        core_global.h \
    ibasegameelement.h \
    infinitydouble.h \
    imap.h \
    maps/listbsemap.h \
    coreconst.h \
    connection/simpleconnection.h \
    connection/mailboxelement.h \
    util/baseutil.h \
    GameElements/basetank.h \
    GameElements/basebulet.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
