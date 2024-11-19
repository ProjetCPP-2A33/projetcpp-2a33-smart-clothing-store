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

QList<Equipment> Equipment::afficher(const QSqlDatabase &db) {
    QList<Equipment> equipmentList;
    QSqlQuery query(db);

    if (!query.exec("SELECT id, name, type, quantity, utility FROM equipments")) {
        qDebug() << "Retrieve Error:" << query.lastError().text();
        return equipmentList; // Return empty list on failure
    }

    while (query.next()) {
        QString id = query.value(0).toString();
        QString name = query.value(1).toString();
        QString type = query.value(2).toString();
        int quantity = query.value(3).toInt();
        QString utility = query.value(4).toString();

        Equipment equipment(id, name, type, quantity, utility);
        equipmentList.append(equipment);
    }

    return equipmentList;
}

Equipment Equipment::rechercher(const QSqlDatabase &db, const QString &id) {
    QSqlQuery query(db);
    query.prepare("SELECT id, name, type, quantity, utility FROM equipments WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Find Error:" << query.lastError().text();
        return Equipment("", "", "", 0, "");  // Return empty object on error
    }

    if (query.next()) {
        QString name = query.value(1).toString();
        QString type = query.value(2).toString();
        int quantity = query.value(3).toInt();
        QString utility = query.value(4).toString();

        return Equipment(id, name, type, quantity, utility);
    } else {
        return Equipment("", "", "", 0, "");
    }
}

QList<Equipment> Equipment::rechercherParNom(const QSqlDatabase &db, const QString &name) {
    QList<Equipment> equipments;
    QSqlQuery query(db);
    query.prepare("SELECT id, name, type, quantity, utility FROM equipments WHERE name LIKE ?");
    query.addBindValue("%" + name + "%");  // Using LIKE for partial match (contains)
    query.exec();

    while (query.next()) {
        equipments.append(Equipment(query.value(0).toString(),
                                    query.value(1).toString(),
                                    query.value(2).toString(),
                                    query.value(3).toInt(),
                                    query.value(4).toString()));
    }
    return equipments;
}

QList<Equipment> Equipment::trier(const QSqlDatabase &db, bool ascending) {
    QList<Equipment> equipments;

    QString sortOrder = ascending ? "ASC" : "DESC";
    QSqlQuery query(db);
    query.prepare("SELECT id, name, type, quantity, utility FROM equipments ORDER BY quantity " + sortOrder);

    if (!query.exec()) {
        qDebug() << "Error sorting equipments: " << query.lastError().text();
        return equipments;
    }

    while (query.next()) {
        equipments.append(Equipment(query.value("id").toString(),
                                    query.value("name").toString(),
                                    query.value("type").toString(),
                                    query.value("quantity").toInt(),
                                    query.value("utility").toString()));
    }

    return equipments;
}

bool Equipment::mettreAJour(const QSqlDatabase &db) {
    QSqlQuery query(db);
    query.prepare("UPDATE equipments SET name = ?, type = ?, quantity = ?, utility = ? WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(type);
    query.addBindValue(quantity);
    query.addBindValue(utility);
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "Update Error: " << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() == 0) {
        qDebug() << "No rows updated. Check the equipment ID.";
        return false;
    }

    return true;
}

int Equipment::getTotalEquipmentCount(QSqlDatabase db) {
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM equipments");
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int Equipment::getEquipmentCountAboveThreshold(int threshold, QSqlDatabase db) {
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM equipments WHERE quantity > :threshold");
    query.bindValue(":threshold", threshold);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QList<Equipment> Equipment::getEquipmentsBelowThreshold(int threshold, QSqlDatabase db) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM equipments WHERE quantity <= :threshold");
    query.bindValue(":threshold", threshold);
    QList<Equipment> list;
    if (query.exec()) {
        while (query.next()) {
            Equipment eq(query.value(0).toString(),
                         query.value(1).toString(),
                         query.value(2).toString(),
                         query.value(3).toInt(),
                         query.value(4).toString());
            list.append(eq);
        }
    }
    return list;
}

QList<Equipment> Equipment::getEquipmentsAboveThreshold(int threshold, QSqlDatabase db) {
    QSqlQuery query(db);
    query.prepare("SELECT * FROM equipments WHERE quantity > :threshold");
    query.bindValue(":threshold", threshold);
    QList<Equipment> list;
    if (query.exec()) {
        while (query.next()) {
            while (query.next()) {
                Equipment eq(query.value(0).toString(),
                             query.value(1).toString(),
                             query.value(2).toString(),
                             query.value(3).toInt(),
                             query.value(4).toString());
                list.append(eq);
            }
        }
    }
    return list;
}