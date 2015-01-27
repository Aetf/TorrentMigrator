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
    models/recordstransformerfactory.h \
    logic/dialoghelper.h \
    models/transformermodel.h

SOURCES += main.cpp \
    models/recordsmodel.cpp \
    models/recordsaccessorfactory.cpp \
    models/recordstransformerfactory.cpp \
    logic/dialoghelper.cpp \
    models/transformermodel.cpp

RESOURCES += qml.qrc

OTHER_FILES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
