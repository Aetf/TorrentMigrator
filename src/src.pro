include(../defaults.pri)
TEMPLATE =  lib

QT       -= gui

TARGET   =  torrentBackends
CONFIG   -= app_bundle

LIBS += -L/home/aetf/lib -lQBencode

SOURCES += \
    torrentrecord.cpp \
    basictorrentmodel.cpp \
    utorrentaccessor.cpp \
    utils.cpp \
    libtorrentaccessor.cpp \
    simpletorrentinfo.cpp

HEADERS += \
    torrentrecord.h \
    irecordsaccessor.h \
    basictorrentmodel.h \
    utorrentaccessor.h \
    utils.h \
    libtorrentaccessor.h \
    simpletorrentinfo.h
