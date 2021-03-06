#-------------------------------------------------
#
# Project created by QtCreator 2018-05-18T22:39:49
#
#-------------------------------------------------

QT       -= gui

QT += quick
QT += qml
TARGET = Connection
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        connection.cpp \
    console.pb.cc \
    console.grpc.pb.cc \
    connect.cpp \
    greeter.cpp \
    listinstrument.cpp \
    startinstrument.cpp \
    getlasttime.cpp

HEADERS += \
        connection.h \
    console.pb.h \
    console.grpc.pb.h \
    connect.h \
    greeter.h \
    listinstrument.h \
    startinstrument.h \
    getlasttime.h
unix {
    target.path = /usr/lib
    INSTALLS += target
    #CONFIG += link_pkgconfig
    #PKGCONFIG += protobuf
    #PKGCONFIG += grpc++
}

DISTFILES += \
    ../lib/debug/qml/LastTime.qml
