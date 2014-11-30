include(../defaults.pri)
TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle

# Link to library to be tested
LIBS += -L../src -ltorrentBackends
LIBS += -L/home/aetf/lib -lQBencode

# Include gtest headers as a system header to avoid compiler warnings in it.
QMAKE_INCDIR += gtest

SOURCES += gtest/gtest-all-strip.cc gtest/main.cpp

# Test runner wrappers
wrapper_scripts = runtests.sh runtests.bat
test_wrappers.commands = cd $${PWD} && cp $${wrapper_scripts} $${OUT_PWD}
OTHER_FILES += $${wrapper_scripts}
QMAKE_EXTRA_TARGETS += test_wrappers
PRE_TARGETDEPS += test_wrappers
