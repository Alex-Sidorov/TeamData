#-------------------------------------------------
#
# Project created by QtCreator 2020-03-25T15:33:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += c++14

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ActiveObject/abstracttask.cpp \
    ActiveObject/proxyactiveobject.cpp \
    ActiveObject/scheduler.cpp \
    BaseClient/base_client.cpp \
    FileSystemWatcher/filesystem_informer.cpp \
    BaseServer/base_server.cpp \
    Tasks/taskdirchanged.cpp \
    Tasks/taskfilechanged.cpp \
    Tasks/taskrecvfile.cpp \
    Tasks/taskrecvmsg.cpp \
    Tasks/tasksendfile.cpp \
    Tasks/tasksendmsg.cpp \
    Settings/settings.cpp \
    Workers/workerclientdatabase.cpp \
    Workers/workermetadata.cpp \
    Workers/workerremoteclient.cpp

HEADERS += \
        mainwindow.h \
    ActiveObject/abstracttask.h \
    ActiveObject/proxyactiveobject.h \
    ActiveObject/scheduler.h \
    BaseClient/base_client.h \
    FileSystemWatcher/filesystem_informer.h \
    BaseServer/base_server.h \
    Tasks/taskdirchanged.h \
    Tasks/taskfilechanged.h \
    Tasks/taskrecvfile.h \
    Tasks/taskrecvmsg.h \
    Tasks/tasksendfile.h \
    Tasks/tasksendmsg.h \
    Settings/settings.h \
    Workers/workerclientdatabase.h \
    Workers/workermetadata.h \
    Workers/workerremoteclient.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
