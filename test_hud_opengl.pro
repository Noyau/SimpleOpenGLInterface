#-------------------------------------------------
#
# Project created by QtCreator 2015-01-22T17:53:40
#
#-------------------------------------------------

QT       += opengl widgets

TARGET = test_hud_opengl

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    src/bgcontainer.cpp \
    src/container.cpp \
    src/frame.cpp \
    src/glwidget.cpp \
    src/hudcontainer.cpp \
    src/icon.cpp \
    src/main.cpp \
    src/object.cpp \
    src/openglutils.cpp \
    src/utils.cpp

HEADERS += \
    src/bgcontainer.hpp \
    src/container.hpp \
    src/frame.hpp \
    src/glwidget.hpp \
    src/hudcontainer.hpp \
    src/icon.hpp \
    src/object.hpp \
    src/openglutils.hpp \
    src/utils.hpp

contains(QT_CONFIG, opengles.) {
    contains(QT_CONFIG, angle): \
        warning("Qt was built with ANGLE, which provides only OpenGL ES 2.0 on top of DirectX 9.0c")
    error("This example requires Qt to be configured with -opengl desktop")
}
