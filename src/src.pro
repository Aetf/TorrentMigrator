include(../defaults.pri)
TEMPLATE =  lib

QT       -= gui

TARGET   =  torrentBackends
CONFIG   -= app_bundle

INCLUDEPATH += "/home/aetf/include/QBencode"

SOURCES += \
    torrentrecord.cpp \
    basictorrentmodel.cpp \
    utorrentaccessor.cpp \
    utils.cpp

HEADERS += \
    torrentrecord.h \
    irecordsaccessor.h \
    basictorrentmodel.h \
    utorrentaccessor.h \
    utils.h
