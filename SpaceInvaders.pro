#-------------------------------------------------
#
# Project created by QtCreator 2016-01-20T12:06:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SpaceInvaders-master
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app

#Ligne pour A. CASALI
QMAKE_MAC_SDK = macosx10.11

SOURCES += main.cpp \
    sounds.cpp

HEADERS += \
    const.h \
    sounds.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML-2.3.2/lib/release/ -lsfml-audio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML-2.3.2/lib/debug/ -lsfml-audio
else:unix: LIBS += -L$$PWD/SFML-2.3.2/lib/ -lsfml-audio

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/SFML-2.3.2/lib/release/ -lsfml-network
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/SFML-2.3.2/lib/debug/ -lsfml-network
else:unix: LIBS += -L$$PWD/SFML-2.3.2/lib/ -lsfml-network

INCLUDEPATH += $$PWD/SFML-2.3.2/include
DEPENDPATH += $$PWD/SFML-2.3.2/include
