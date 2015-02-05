include(../defaults.pri)

TEMPLATE = app
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG   -= app_bundle

# link to internal src libraries
unix:PRE_TARGETDEPS += $$OUT_PWD/../src/libtorrentBackends.a
win32:PRE_TARGETDEPS += $$OUT_PWD/../src/torrentBackends.lib
LIBS     += -L../src -ltorrentBackends

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
