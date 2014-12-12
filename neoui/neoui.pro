include(../defaults.pri)

TEMPLATE = app
QT       += core qml quick widgets
CONFIG   -= app_bundle

# link to libraries
PRE_TARGETDEPS += ../src/libtorrentBackends.a
LIBS     += -L../src -ltorrentBackends
LIBS     += -lQBencode -lPocoFoundation

HEADERS += \
    models/recordsmodel.h \
    models/recordsaccessorfactory.h \
    models/recordsaccessorobject.h

SOURCES += main.cpp \
    models/recordsmodel.cpp \
    models/recordsaccessorfactory.cpp

RESOURCES += qml.qrc

OTHER_FILES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
