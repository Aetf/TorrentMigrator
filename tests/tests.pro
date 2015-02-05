include(../defaults.pri)
TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

DESTDIR = $$OUT_PWD

# link to internal src libraries
unix:PRE_TARGETDEPS += $$OUT_PWD/../src/libtorrentBackends.a
win32:PRE_TARGETDEPS += $$OUT_PWD/../src/torrentBackends.lib
LIBS   += -L../src -ltorrentBackends

# Include gtest headers as a system header to avoid compiler warnings in it.
QMAKE_INCDIR += gtest

SOURCES += gtest/gtest-all-strip.cc gtest/main.cpp \
    test_utorrentaccessor.cpp \
    test_libtorrentaccessor.cpp

OTHER_FILES += scripts/*

# Test runner wrappers
unix:test_wrappers.commands = cd $${PWD} && cp scripts/* $${OUT_PWD}
win32:test_wrappers.commands = cd /d $${PWD} && xcopy \"scripts/*\" \"$${OUT_PWD}\"
QMAKE_EXTRA_TARGETS += test_wrappers
PRE_TARGETDEPS += test_wrappers
