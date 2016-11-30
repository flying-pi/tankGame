#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T13:16:19
#
#-------------------------------------------------

QT       += core gui network opengl

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameView
TEMPLATE = app

QMAKE_LFLAGS += -rdynamic

SOURCES += main.cpp\
        mainwindow.cpp \
    field.cpp

HEADERS  += mainwindow.h \
    field.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Core/release/ -lCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Core/debug/ -lCore
else:unix: LIBS += -L$$OUT_PWD/../Core/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core
