#include "equipment.h"

Equipment::Equipment(const QString &id, const QString &name, const QString &type, int quantity, const QString &utility)
    : id(id), name(name), type(type), quantity(quantity), utility(utility) {}

bool Equipment::ajouter(const QSqlDatabase &db) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO equipments (id, name, type, quantity, utility) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(id);
    query.addBindValue(name);
    query.addBindValue(type);
    query.addBindValue(quantity);
    query.addBindValue(utility);

    if (!query.exec()) {
        qDebug() << "Add Error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Equipment::supprimer(const QSqlDatabase &db, const QString &id) {
    QSqlQuery query(db);
    query.prepare("DELETE FROM equipments WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Delete Error:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "No equipment found with ID:" << id;
        return false;
    }

    return true;
}
