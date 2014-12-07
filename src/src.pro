include(../defaults.pri)
TEMPLATE =  lib

QT       -= gui

TARGET   =  torrentBackends
CONFIG   -= app_bundle
CONFIG   += staticlib
LIBS     += -lQBencode

SOURCES  += \
    torrentrecord.cpp \
    basictorrentmodel.cpp \
    utorrentaccessor.cpp \
    utils.cpp \
    libtorrentaccessor.cpp \
    simpletorrentinfo.cpp \
    basictorrentitem.cpp

HEADERS  += \
    torrentrecord.h \
    irecordsaccessor.h \
    basictorrentmodel.h \
    utorrentaccessor.h \
    utils.h \
    libtorrentaccessor.h \
    simpletorrentinfo.h \
    basictorrentitem.h
