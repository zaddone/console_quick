# Add more folders to ship with the application, here
folder_01.source = qml/console_quick
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    client.cpp \
    console.grpc.pb.cc \
    console.pb.cc \
    view.cpp \
    showlist.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    client.h \
    console.grpc.pb.h \
    console.pb.h \
    view.h \
    showlist.h


QT += concurrent

unix: CONFIG += link_pkgconfig
unix: CONFIG += c++11

unix: PKGCONFIG += protobuf

unix: PKGCONFIG += grpc
unix: PKGCONFIG += grpc++

OTHER_FILES += \
    qml/console_quick/Show.qml
