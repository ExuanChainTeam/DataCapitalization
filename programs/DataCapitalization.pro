QT += core
QT -= gui

CONFIG += c++11

TARGET = DataCapitalization
CONFIG += console
CONFIG -= app_bundle


SOURCES += main.cpp \
    chelibio.cpp \
    ipfs/cipfsbase.cpp \
    cloudComputing/cbaseobject.cpp \
    dataSource/cdatarelation.cpp \
    dataSource/cdatatransfer.cpp \
    ipfs/cipfshandledata.cpp \
    dataSource/cdatabaseobject.cpp \
    cloudComputing/ccomputationmodel.cpp \
    cloudComputing/ccomputationdata.cpp \
    cloudComputing/ccomputationformula.cpp \
    cloudComputing/ccomputationresult.cpp \
    test.cpp


HEADERS += \
    chelibio.h \
    ipfs/cipfsbase.h \
    cloudComputing/cbaseobject.h \
    fheconfig.h \
    dataSource/cdatarelation.h \
    dataSource/cdatatransfer.h \
    ipfs/cipfshandledata.h \
    dataSource/cdatabaseobject.h \
    cloudComputing/ccomputationmodel.h \
    cloudComputing/ccomputationdata.h \
    cloudComputing/ccomputationformula.h \
    cloudComputing/ccomputationresult.h \
    test.h \
    globalfunction.h \
    jsonconfig.h \
    curlconfig.h

unix:!macx: LIBS += -L$$PWD/../libraries/HElib/src/ -lfhe

INCLUDEPATH += $$PWD/../libraries/HElib/src
DEPENDPATH += $$PWD/../libraries/HElib/src

unix:!macx: PRE_TARGETDEPS += $$PWD/../libraries/HElib/src/libfhe.a

unix:!macx: LIBS += -lntl

unix:!macx: LIBS += -lsqlite3

unix:!macx: LIBS += -lgmp

unix:!macx: LIBS += -ljsoncpp

unix:!macx: LIBS += -lcurl
