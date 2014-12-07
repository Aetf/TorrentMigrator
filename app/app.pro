include(../defaults.pri)

TEMPLATE = app
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG   -= app_bundle


PRE_TARGETDEPS += ../src/libtorrentBackends.a
LIBS     += -L../src -ltorrentBackends
LIBS     += -lQBencode

SOURCES  += \
    main.cpp \
    mainwindow.cpp \
    utorrentconfpanel.cpp \
    qbittorrentconfpanel.cpp

HEADERS  += \
    mainwindow.h \
    utorrentconfpanel.h \
    qbittorrentconfpanel.h \
    abstractconfpanel.h

FORMS    += \
    mainwindow.ui \
    utorrentconfpanel.ui \
    qbittorrentconfpanel.ui
