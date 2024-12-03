#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Produit {
public:
    Produit(QSqlDatabase* db);
    int countUnavailableProducts();

private:
    QSqlDatabase* database;
};

#endif // PRODUIT_H
