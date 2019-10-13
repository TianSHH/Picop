QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Picop
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += ./ \
	include/ \
    source/ 

SOURCES += \
        source/main.cpp \
        source/mainwindow.cpp \
    source/dialogquantifylevel.cpp \
    source/dialogsamplingrate.cpp \
    source/dialogbitplane.cpp \
    source/dialoghistogram.cpp \
    source/dialoggrayscalethreshold.cpp \
    source/dialoglinearpointoperation.cpp \
    # source/dialognolinearpointoperation.cpp

HEADERS += \
        include/mainwindow.h \
    include/dialogquantifylevel.h \
    include/dialogsamplingrate.h \
    include/dialogbitplane.h \
    include/dialoghistogram.h \
    include/dialoggrayscalethreshold.h \
    include/dialoglinearpointoperation.h \
    # include/dialognolinearpointoperation.h

    DESTDIR = bin
    OBJECTS_DIR = debug/obj
    MOC_DIR = debug/moc
    # RCC_DIR
    # UI_DIR
