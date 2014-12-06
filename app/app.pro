include(../defaults.pri)

TEMPLATE = app
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG   -= app_bundle


# Link to library to be tested
PRE_TARGETDEPS += ../src/libtorrentBackends.a
LIBS     += -L../src -ltorrentBackends
LIBS     += -L/home/aetf/lib -lQBencode

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
