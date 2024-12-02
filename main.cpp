#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
<<<<<<< HEAD
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test=c.createconnection();
    MainWindow w;
    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                 QObject::tr("connection successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                          QObject::tr("connection failed.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
=======
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

>>>>>>> 6970123e40de339b0298ce361cc13ba1279501a0
    return a.exec();
}
