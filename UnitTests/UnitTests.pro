QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += tst_agent.cc \
    ../Student/agent.cpp \
    ../course/Course/gameexception.cpp \
    ../course/Course/rangeexception.cpp \
    ../course/Course/stateexception.cpp


HEADERS += ../Student/agent.h \
    ../course/Course/gameexception.h \
    ../course/Course/rangeexception.h \
    ../course/Course/stateexception.h

INCLUDEPATH += ../Student/
