TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -O4

SOURCES += main.cpp \
    base_encoder.cpp \
    base_decoder.cpp \
    mp3_decoder.cpp \
    mp3_encoder.cpp \
    raw_head.cpp \
    base_head.cpp

HEADERS += \
    base_encoder.h \
    base_decoder.h \
    head.h \
    mp3_decoder.h \
    mp3_encoder.h \
    base_head.h \
    raw_head.h \
    io.h
