#-------------------------------------------------
#
# Project created by QtCreator 2019-01-28T12:40:37
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageDownloader
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    model.cpp \
    download.cpp \
    image.cpp \
    controller.cpp \
    history.cpp \
    changepathdialog.cpp \
    historydialog.cpp \
    imagelabel.cpp

HEADERS += \
        mainwindow.h \
    model.h \
    download.h \
    image.h \
    controller.h \
    constants.h \
    history.h \
    changepathdialog.h \
    historydialog.h \
    imagelabel.h

FORMS += \
        mainwindow.ui \
    changepathdialog.ui \
    historydialog.ui