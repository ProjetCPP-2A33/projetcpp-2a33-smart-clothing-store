<<<<<<< HEAD
QT       += core gui sql
=======
QT       += core gui sql network
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    clientswindow.cpp \
    connection.cpp \
<<<<<<< HEAD
=======
    imagedelegate.cpp \
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
    main.cpp \
    mainwindow.cpp

HEADERS += \
    client.h \
    clientswindow.h \
    connection.h \
<<<<<<< HEAD
=======
    imagedelegate.h \
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
    mainwindow.h

FORMS += \
    clientswindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

