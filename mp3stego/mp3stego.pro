TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -O4

SOURCES += main.cpp \
    file_func.cpp

HEADERS += \
    basehead.hpp \
    rawhead.hpp \
    head.hpp \
    file_func.hpp \
    mp3encoder.hpp \
    mp3decoder.hpp
