QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

greaterThan(QT_MAJOR_VERSION, 4) {
    TARGET_ARCH=$${QT_ARCH}
} else {
    TARGET_ARCH=$${QMAKE_HOST.arch}
}

contains(TARGET_ARCH, x86_64) {
    ARCHITECTURE = x64
} else {
    ARCHITECTURE = x86
}

win32-g++:contains(ARCHITECTURE, x86): {
    INCLUDEPATH += D:/Software/boost/boost_1_83_0/boost_mingw830_32/include/boost-1_83
    LIBS += "-LD:/Software/boost/boost_1_83_0/boost_mingw830_32/lib"
}

SOURCES += main.cpp \
    object.cpp \
    attribute.cpp \
    element.cpp \
    shell.cpp \
    listofvalues.cpp \
    yaodstructure.cpp \
    keywordsdescription.cpp \
    encodingtype.cpp \
    parserstringddl.cpp \
    yaodparser.cpp \
    validatoryaod.cpp \
    printyaod.cpp \
    filemanager.cpp \
    dataparser.cpp

HEADERS += \
    object.h \
    element.h \
    attribute.h \
    shell.h \
    listofvalues.h \
    yaodstructure.h \
    keywordsdescription.h \
    encodingtype.h \
    parserstringddl.h \
    yaodparser.h \
    exception.h \
    validatoryaod.h \
    printyaod.h \
    filemanager.h \
    dataparser.h
