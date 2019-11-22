QT += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = picop
TEMPLATE = app

# g++编译选项
# 关闭g++编译时的无关警告
QMAKE_CXXFLAGS += -w

# 可以理解为qmake识别的编译选项
# 标准为c++17,多线程
CONFIG += c++17 \
          thread
# 通过设置CONFIG也可以达到同样的效果,编译器尽可能少得输出警告信息
# CONFIG += warn_off

# tasks.json中编译指令有一选项 "-spec",
#                           "linux-g++-64",
# 作用是编译时读取/opt/Qt5.9.8/5.9.8/gcc_64/mkspecs/linux-g++/下的配置
# 编译时会产生一下选项
# -I/opt/Qt5.9.8/5.9.8/gcc_64/mkspecs/linux-g++
# 按照预设配置编译
# QMAKE_CXXFLAGS中的用户自定义选项会覆盖以上默认配置


INCLUDEPATH += ./ \
	include/ \
    source/ \
    /usr/local/include/opencv4/

LIBS += /usr/local/lib/libopencv*

SOURCES += \
        source/main.cpp \
        source/mainwindow.cpp \
    source/dialogquantifylevel.cpp \
    source/dialogsamplingrate.cpp \
    source/dialogbitplane.cpp \
    source/dialoghistogram.cpp \
    source/dialoggrayscalethreshold.cpp \
    source/dialoglinearpointoperation.cpp \
    source/dialoglogtransformation.cpp \ 
    source/dialogpowertransformation.cpp \
    source/dialogtranslation.cpp \
    source/dialogrotation.cpp \
    source/dialogscaling.cpp \
    source/smoothmethod.cpp \
    source/SharpenMethod.cpp \
    source/FilterMethod.cpp \
    source/ColorMethod.cpp \
    source/EdgeMethod.cpp \
    source/FormatMethod.cpp \
    source/SpectrogramMethod.cpp \
    source/qcustomplot.cpp

HEADERS += \
        include/mainwindow.h \
    include/dialogquantifylevel.h \
    include/dialogsamplingrate.h \
    include/dialogbitplane.h \
    include/dialoghistogram.h \
    include/dialoggrayscalethreshold.h \
    include/dialoglinearpointoperation.h \
    include/dialoglogtransformation.h \
    include/dialogpowertransformation.h \
    include/dialogtranslation.h \
    include/dialogrotation.h \
    include/dialogscaling.h \
    include/smoothmethod.h \
    include/SharpenMethod.h \
    include/FilterMethod.h \
    include/ColorMethod.h \
    include/EdgeMethod.h \
    include/FormatMethod.h \
    include/SpectrogramMethod.h \
    include/qcustomplot.h


DESTDIR = ./bin
OBJECTS_DIR = ./debug/obj
MOC_DIR = ./debug/moc
# RCC_DIR
# UI_DIR

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable
