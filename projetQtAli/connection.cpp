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
    db.setDatabaseName("CPP_Project");//inserer le nom de la source de données ODBC
    db.setUserName("Mayress");//inserer nom de l'utilisateur
    db.setPassword("oracle");//inserer mot de passe de cet utilisateur

    if (db.open()) {
        test = true;
    } else {
        qDebug() << "Database Error: " << db.lastError().text();
    }

    return test;
}
