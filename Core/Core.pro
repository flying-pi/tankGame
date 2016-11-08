#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T13:17:33
#
#-------------------------------------------------

QT       -= gui

TARGET = Core
TEMPLATE = lib

CONFIG += c++11

DEFINES += CORE_LIBRARY

SOURCES += core.cpp \
    infinitydouble.cpp \
    baseElenents/basetank.cpp \
    imap.cpp \
    ibasegameelement.cpp \
    maps/listbsemap.cpp \

HEADERS += core.h\
        core_global.h \
    ibasegameelement.h \
    infinitydouble.h \
    baseElenents/basetank.h \
    imap.h \
    maps/listbsemap.h \
    coreconst.h
    util/baseutil.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
