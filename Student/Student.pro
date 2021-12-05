TEMPLATE = app
TARGET = Game

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    Utils/helper.cpp \
    agent.cpp \
    cardbagdialog.cpp \
    carditem.cpp \
    cardpreviewdialog.cpp \
    main.cc \
    mapdialog.cpp \
    offlinereader.cpp \
    ownlocationaction.cpp \
    sendagentaction.cpp \
    shuffleanddrawaction.cpp \
    startdialog.cpp \
    mainwindow.cpp \
    strengthenconnections.cpp

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../course/Course/release/ -lCourse
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../course/Course/debug/ -lCourse
else:unix: LIBS += \
    -L$$OUT_PWD/../course/Course/ -lCourse

INCLUDEPATH += \
    $$PWD/../course/Course

DEPENDPATH += \
    $$PWD/../course/Course

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../course/Course/release/libCourse.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../course/Course/debug/libCourse.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../course/Course/release/Course.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../course/Course/debug/Course.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../course/Course/libCourse.a

HEADERS += \
    Utils/helper.h \
    agent.h \
    cardbagdialog.h \
    carditem.h \
    cardpreviewdialog.h \
    mapdialog.h \
    offlinereader.h \
    ownlocationaction.h \
    sendagentaction.h \
    shuffleanddrawaction.h \
    startdialog.hh\
    mainwindow.h \
    strengthenconnections.h

FORMS += \
    cardbagdialog.ui \
    cardpreviewdialog.ui \
    mapdialog.ui \
    mainwindow.ui \
    startdialog.ui

RESOURCES += \
    images.qrc \
    introText.qrc \
#    offlinedata.qrc \
    offlinedata.qrc
