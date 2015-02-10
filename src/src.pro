include(../defaults.pri)
TEMPLATE =  lib

QT       -= gui
QT       += concurrent

TARGET   =  torrentBackends
CONFIG   -= app_bundle
CONFIG   += staticlib

win32:DESTDIR = $$OUT_PWD/

SOURCES  += \
    torrentrecord.cpp \
    basictorrentmodel.cpp \
    utorrentaccessor.cpp \
    utils.cpp \
    libtorrentaccessor.cpp \
    simpletorrentinfo.cpp \
    basictorrentitem.cpp \
    devicemaptransformer.cpp \
    pathregextransformer.cpp \
    transfermanager.cpp

HEADERS  += \
    torrentrecord.h \
    irecordsaccessor.h \
    basictorrentmodel.h \
    utorrentaccessor.h \
    utils.h \
    libtorrentaccessor.h \
    simpletorrentinfo.h \
    basictorrentitem.h \
    irecordstransformer.h \
    devicemaptransformer.h \
    pathregextransformer.h \
    transfermanager.h
