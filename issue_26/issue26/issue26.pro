#-------------------------------------------------
#
# Project created by QtCreator 2020-02-20T20:01:09
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = issue26
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += "C:\OpenCV-QT\install\include"
LIBS += -L"C:\OpenCV-QT\install\x86\mingw\bin" \
    libopencv_core320 \
    libopencv_highgui320 \
    libopencv_videoio320 \
    libopencv_imgcodecs320 \
    libopencv_imgproc320 \
    libopencv_features2d320 \
    libopencv_calib3d320

SOURCES += main.cpp
