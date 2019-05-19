#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T14:55:56
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lib3000
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
    loginwindow.cpp \
    adminmenu.cpp \
    book.cpp \
    addbook.cpp \
    editbook.cpp \
    userinfo.cpp \
    editreader.cpp \
    readerwindow.cpp \
    register_signup.cpp \
    addreader.cpp \
    storage.cpp \
    orders.cpp

HEADERS += \
    loginwindow.h \
    adminmenu.h \
    book.h \
    addbook.h \
    editbook.h \
    userinfo.h \
    editreader.h \
    readerwindow.h \
    register_signup.h \
    addreader.h \
    storage.h \
    orders.h

FORMS += \
    loginwindow.ui \
    adminmenu.ui \
    addbook.ui \
    editbook.ui \
    editreader.ui \
    readerwindow.ui \
    register_signup.ui \
    addreader.ui

RESOURCES += \
    img.qrc
