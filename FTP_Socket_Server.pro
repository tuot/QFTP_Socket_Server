#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T09:36:24
#
#-------------------------------------------------

QT       += core gui
QT +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FTP_Socket_Server
TEMPLATE = app


SOURCES += main.cpp\
        mymainwindow.cpp \
    ftpserver.cpp \
    dataconnection.cpp \
    ftpcommand.cpp \
    ftpcontrolconnection.cpp \
    ftplistcommand.cpp \
    ftpretrcommand.cpp \
    ftpstorcommand.cpp

HEADERS  += mymainwindow.h \
    ftpserver.h \
    dataconnection.h \
    ftpcommand.h \
    ftpcontrolconnection.h \
    ftplistcommand.h \
    ftpretrcommand.h \
    ftpstorcommand.h

FORMS    += mymainwindow.ui

RESOURCES += \
    res.qrc
