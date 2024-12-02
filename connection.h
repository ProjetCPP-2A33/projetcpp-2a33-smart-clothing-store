#ifndef CONNECTION_H
#define CONNECTION_H
<<<<<<< HEAD
#include <QSqlDatabase>
class Connection
{
    QSqlDatabase db;
public:
    Connection();
    bool createconnection();
    void closeConnection();
};
#endif // CONNECTION_H

=======

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Connection {
    QSqlDatabase db;

public:
    Connection();
    bool createconnect();
    void closeconnection();
};

#endif // CONNECTION_H
>>>>>>> 6970123e40de339b0298ce361cc13ba1279501a0
