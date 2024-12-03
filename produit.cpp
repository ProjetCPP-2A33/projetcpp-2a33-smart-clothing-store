#include "produit.h"

Produit::Produit(QSqlDatabase* db) : database(db) {}

int Produit::countUnavailableProducts() {
    int count = 0;

    QSqlQuery query(*database);
    query.prepare("SELECT COUNT(*) FROM produits WHERE statut_prod = 0");

    if (query.exec() && query.next()) {
        count = query.value(0).toInt();
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    return count;
}

