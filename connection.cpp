#include "connection.h"
#include <QMessageBox>

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test = false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("tast-bd"); // Nom de la source de données
    db.setUserName("nawres");      // Nom de l'utilisateur
    db.setPassword("nawres");      // Mot de passe

    if (db.open()) {
        test = true;
    }
    if (!db.isOpen()) {
        QMessageBox::critical(nullptr, "Database Error", "Database is not open.");
        return false;
    }

    return test;
}

void Connection::closeconnection()
{
    db.close();
}
