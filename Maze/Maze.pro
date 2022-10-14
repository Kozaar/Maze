QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/controllerAlg.cpp \
    Interface/caveview.cpp \
    Interface/mazeview.cpp \
    Interface/scene.cpp \
    Model/cave.cpp \
    Model/cavefile.cpp \
    Model/maze.cpp \
    Model/mazefile.cpp \
    main.cpp \
    Interface/interface.cpp

HEADERS += \
    Controller/controllerAlg.h \
    Interface/caveview.h \
    Interface/interface.h \
    Interface/mazeview.h \
    Interface/scene.h \
    Model/cave.h \
    Model/cavefile.h \
    Model/maze.h \
    Model/mazefile.h

FORMS += \
    Interface/interface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
