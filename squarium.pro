#-------------------------------------------------
#
# Project created by QtCreator 2018-09-06T17:46:28
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = squarium
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


RC_ICONS = micon.ico

SOURCES += \
        main.cpp \
        strange_squarium.cpp \
    gaming.cpp \
    abstractitem.cpp \
    fooditem.cpp \
    mscene.cpp \
    gold.cpp \
    fishmodel.cpp \
    gubi.cpp \
    meatfish.cpp \
    momi.cpp \
    shark.cpp \
    petmodel.cpp \
    snails.cpp \
    alienmodel.cpp \
    bluemonster.cpp \
    foodie.cpp \
    mermaid.cpp \
    dolphin.cpp \
    bang.cpp \
    feeder.cpp \
    tuna.cpp \
    destructor.cpp \
    missile.cpp \
    boss.cpp \
    selectwin.cpp

HEADERS += \
        strange_squarium.h \
    gaming.h \
    abstractitem.h \
    fooditem.h \
    mscene.h \
    gold.h \
    fishmodel.h \
    gubi.h \
    meatfish.h \
    momi.h \
    shark.h \
    petmodel.h \
    snails.h \
    alienmodel.h \
    bluemonster.h \
    foodie.h \
    mermaid.h \
    dolphin.h \
    bang.h \
    feeder.h \
    tuna.h \
    destructor.h \
    missile.h \
    boss.h \
    selectwin.h

FORMS += \
        strange_squarium.ui \
    gaming.ui \
    selectwin.ui

RESOURCES += \
    src.qrc

DISTFILES +=
