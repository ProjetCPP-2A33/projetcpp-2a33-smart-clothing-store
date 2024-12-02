#include "connection.h"
<<<<<<< HEAD
Connection::Connection(){}
bool Connection::createconnection()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("tast-bd");
db.setUserName("nawres");
db.setPassword("nawres");
if (db.open())
{
    return  true;
}
}
void Connection::closeConnection(){db.close();}

=======
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
>>>>>>> 6970123e40de339b0298ce361cc13ba1279501a0
