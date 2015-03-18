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


SOURCES += main_delayer.cpp \
    SimpleCrypt/SimpleCrypt.cpp \
    PasswordSerializer.cpp \
    ChangePasswordDialog.cpp \
    PasswordDelayer.cpp \
    PasswordRuleWidget.cpp \
    PasswordDelayer_Filebox.cpp \
    PasswordDelayer_MainBox.cpp \
    PasswordGenerator.cpp

HEADERS  += \
    predefinedValues.hpp \
    functions.hpp \
    SimpleCrypt/SimpleCrypt.hpp \
    PasswordSerializer.hpp \
    ChangePasswordDialog.hpp \
    PasswordDelayer.hpp \
    PasswordRuleWidget.hpp \
    PasswordDelayer_Filebox.hpp \
    PasswordDelayer_MainBox.hpp \
    PasswordGenerator.hpp

FORMS    += \
    ChangePasswordDialog.ui \
    PasswordDelayer.ui \
    PasswordRuleWidget.ui \
    PasswordDelayer_Filebox.ui \
    PasswordDelayer_MainBox.ui \
    PasswordGenerator.ui

OTHER_FILES +=
