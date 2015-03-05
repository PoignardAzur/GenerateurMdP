#-------------------------------------------------
#
# Project created by QtCreator 2013-10-21T15:50:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Generateur
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
    editPasswordFile.cpp \
    SQLite/statement.cpp \
    SQLite/sqlite3.c \
    SQLite/database.cpp \
    retardeurMdp.cpp

HEADERS  += \
    SQLite/statement.hpp \
    SQLite/sqlite3ext.h \
    SQLite/sqlite3.h \
    SQLite/database.hpp \
    predefinedValues.hpp \
    functions.hpp \
    retardeurMdp.h \
    editPasswordFile.hpp

FORMS    += generateurmdp.ui
