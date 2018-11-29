#-------------------------------------------------
#
# Project created by QtCreator 2018-11-05T14:14:18
#
#-------------------------------------------------

QT       += core gui
# sql network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Codec_analyzer
TEMPLATE = app

INCLUDEPATH += C:\Users\Golstats\Downloads\ffmpeg-20181127-1035206-win32-dev\ffmpeg-20181127-1035206-win32-dev\include

#LIBS += -L/usr/local/lib -L/usr/local/cuda/lib64 -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_calib3d -lopencv_features2d -lopencv_xfeatures2d \
#        -lopencv_flann -lopencv_stitching -lopencv_objdetect -lopencv_video -lopencv_ml -fopenmp -lavutil -lavcodec -lavformat -lswscale

#LIBS += -lopencv_cudawarping -lopencv_cudacodec \
#        -lopencv_cudabgsegm -lopencv_cudastereo -lopencv_cudalegacy \
#        -lopencv_cudaobjdetect -lopencv_cudaarithm -lopencv_cudaimgproc -fopenmp
#LIBS += -LC:/Users/Golstats/Downloads/ffmpeg-20181127-1035206-win32-dev/ffmpeg-20181127-1035206-win32-dev/include
LIBS += -LC:\Users\Golstats\Downloads\ffmpeg-20181127-1035206-win32-dev\ffmpeg-20181127-1035206-win32-dev\lib -lavutil -lavcodec -lavformat -lswscale


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp
