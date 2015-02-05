INCLUDEPATH += $$PWD/src
SRC_DIR      = $$PWD

CONFIG      += c++11 warn_on


###################################################################################################
## DEPENDENCIES
###################################################################################################

# QBencode
unix:INCLUDEPATH    += /usr/include/QBencode
win32:INCLUDEPATH   += $$PWD/external/QBencode/src/include
#win32:DEPENDPATH    += $$OUT_PWD/../external/QBencode/
LIBS                += -L$$OUT_PWD/../external/QBencode -lQBencode

# PocoFoundation
#LIBS                += -lPocoFoundation
