QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ajoutewindow.cpp \
    clientswindow.cpp \
    main.cpp \
    mainwindow.cpp \
    modifierwindow.cpp \
    parametreswindow.cpp \
    supprimewindow.cpp

HEADERS += \
    ajoutewindow.h \
    clientswindow.h \
    mainwindow.h \
    modifierwindow.h \
    parametreswindow.h \
    supprimewindow.h

FORMS += \
    ajoutewindow.ui \
    clientswindow.ui \
    mainwindow.ui \
    modifierwindow.ui \
    parametreswindow.ui \
    supprimewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image33.qrc \
    image44.qrc \
    res.qrc
