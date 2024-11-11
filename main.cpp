#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "clientswindow.h" // Inclure la nouvelle fenêtre


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    Connection c;
    bool test = c.createconnect();

    if (test) {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("Database Opened"),
                                 QObject::tr("Connection successful.\nClick Cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Not Opened"),
                              QObject::tr("Connection failed.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}
