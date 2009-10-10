TEMPLATE = app
TARGET = amarokbar
MOC_DIR = .build
OBJECTS_DIR = .build
RCC_DIR = .build
UI_DIR = .build
QT = core gui svg xml

# use OpenGL where available
contains(QT_CONFIG, opengl)|contains(QT_CONFIG, opengles1)|contains(QT_CONFIG, opengles2) {
    QT += opengl
}

# Coolbar
include(Coolbar/Coolbar.pri)

# Amarok extension
include(Amarok/Amarok.pri)

# Test app input files
HEADERS += Window.h
SOURCES += Window.cpp main.cpp
FORMS += Window.ui
