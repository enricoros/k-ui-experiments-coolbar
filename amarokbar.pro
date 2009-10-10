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

# Amarok input files
HEADERS += \
    AmarokCoolbar.h \
    AmarokScene.h \
    EqualizerElement.h \
    ButtonElement.h \
    FlamesElement.h

SOURCES += \
    AmarokCoolbar.cpp \
    AmarokScene.cpp \
    EqualizerElement.cpp \
    ButtonElement.cpp \
    FlamesElement.cpp

# Test app input files
HEADERS += \
    TestWindow.h

SOURCES += \
    TestWindow.cpp \
    main.cpp

FORMS += \
    TestWindow.ui
