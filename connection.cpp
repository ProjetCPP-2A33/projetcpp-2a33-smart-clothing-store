#include "connection.h"

Connection::Connection()
{
}

bool Connection::createconnect()
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
    bool test = false;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("db-test");
    db.setUserName("mehdi");
    db.setPassword("mehdi");

    if (db.open()) {
        test = true;
    } else {
        qDebug() << "Database Error: " << db.lastError().text();
    }

    return test;
}
