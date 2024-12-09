QT       += core gui sql network  printsupport charts serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    client.cpp \
    commande.cpp \
    connection.cpp \
    employe.cpp \
    fournisseur.cpp \
    imagedelegate.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    arduino.h \
    client.h \
    commande.h \
    connection.h \
    employe.h \
    fournisseur.h \
    imagedelegate.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resoureces.qrc \
    ressources.qrc

DISTFILES += \
    intgr.pro.user \
    intgr.pro.user.0f31ab7 \
    intgr.pro.user.4ddb178
