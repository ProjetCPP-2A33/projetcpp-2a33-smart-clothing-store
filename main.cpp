#include "mainwindow.h"
#include "connection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection dbConnection;
    dbConnection.createconnect();

    MainWindow w;
    w.show();
    w.setDatabaseConnection(&dbConnection);

    return a.exec();
}
