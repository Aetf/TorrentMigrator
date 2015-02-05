include(../defaults.pri)

TEMPLATE = app
QT       += core qml quick widgets
CONFIG   -= app_bundle

# link to internal src libraries
unix:PRE_TARGETDEPS += $$OUT_PWD/../src/libtorrentBackends.a
win32:PRE_TARGETDEPS += $$OUT_PWD/../src/torrentBackends.lib
LIBS     += -L../src -ltorrentBackends

INCLUDEPATH += $$PWD

HEADERS += \
    models/recordsmodel.h \
    models/recordsaccessorfactory.h \
    models/recordstransformerfactory.h \
    logic/dialoghelper.h \
    logic/transferhelper.h \
    models/transformermodel.h

SOURCES += main.cpp \
    models/recordsmodel.cpp \
    models/recordsaccessorfactory.cpp \
    models/recordstransformerfactory.cpp \
    logic/dialoghelper.cpp \
    logic/transferhelper.cpp \
    models/transformermodel.cpp

RESOURCES += qml.qrc

OTHER_FILES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
