#include "connection.h"
#include <QDebug>
#include <QSqlError>

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // Set up the connection details
    db.setDatabaseName("source_projet2A"); // Name of the ODBC data source
    db.setUserName("nidhal");              // Database username
    db.setPassword("0000");                // Database password

    // Try to open the database
    if (db.open()) {
        test = true;
        qDebug() << "Database connected successfully!";
    } else {
        qDebug() << "Database connection failed!";
        qDebug() << "Error:" << db.lastError().text();
    }

    return test;
}

QSqlDatabase Connection::getDatabase() {
    return db;
}
