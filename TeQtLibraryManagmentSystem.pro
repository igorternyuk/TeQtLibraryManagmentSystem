#-------------------------------------------------
#
# Project created by QtCreator 2017-11-24T10:29:21
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += c++1z
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DEFINES += DEBUG
TARGET = TeQtLibraryManagmentSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    dialogauthor.cpp \
    dialogcountry.cpp \
    dialogedition.cpp \
    dialoggenre.cpp \
    dialogbooksearch.cpp

HEADERS  += \
    database.hpp \
    dialogauthor.hpp \
    dialogbooksearch.hpp \
    dialogcountry.hpp \
    dialogedition.hpp \
    dialoggenre.hpp \
    mainwindow.hpp

FORMS    += mainwindow.ui \
    dialogauthor.ui \
    dialogcountry.ui \
    dialogedition.ui \
    dialoggenre.ui \
    dialogbooksearch.ui
