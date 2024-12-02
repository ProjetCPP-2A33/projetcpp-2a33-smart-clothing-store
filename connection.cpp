#include "connection.h"
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

