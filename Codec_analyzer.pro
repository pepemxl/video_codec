#-------------------------------------------------
#
# Project created by QtCreator 2018-11-05T14:14:18
#
#-------------------------------------------------

QT       += core gui sql network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Codec_analyzer
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv

INCLUDEPATH += /usr/lib/x86_64-linux-gnu

LIBS += -L/usr/local/lib -L/usr/local/cuda/lib64 -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_calib3d -lopencv_features2d -lopencv_xfeatures2d \
        -lopencv_flann -lopencv_stitching -lopencv_objdetect -lopencv_video -lopencv_ml -fopenmp -lavutil -lavcodec -lavformat -lswscale

LIBS += -lopencv_cudawarping -lopencv_cudacodec \
        -lopencv_cudabgsegm -lopencv_cudastereo -lopencv_cudalegacy \
        -lopencv_cudaobjdetect -lopencv_cudaarithm -lopencv_cudaimgproc -fopenmp


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
