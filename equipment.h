// equipment.h
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Equipment {
private:
    QString id;
    QString name;
    QString type;
    int quantity;
    QString utility;

public:
    Equipment(const QString &id, const QString &name, const QString &type, int quantity, const QString &utility);

    bool ajouter(const QSqlDatabase &db);

    bool supprimer(const QSqlDatabase &db, const QString &id);

    bool mettreAJour(const QSqlDatabase &db);

    static QList<Equipment> afficher(const QSqlDatabase &db);

    static Equipment rechercher(const QSqlDatabase &db, const QString &id);
    static QList<Equipment> rechercherParNom(const QSqlDatabase &db, const QString &name);
    static QList<Equipment> trier(const QSqlDatabase &db, bool ascending);

    static int getTotalEquipmentCount(QSqlDatabase db);
    static int getEquipmentCountAboveThreshold(int threshold, QSqlDatabase db);
    static QList<Equipment> getEquipmentsBelowThreshold(int threshold, QSqlDatabase db);
    static QList<Equipment> getEquipmentsAboveThreshold(int threshold, QSqlDatabase db);

    QString getId() const { return id; }
    QString getName() const { return name; }
    QString getType() const { return type; }
    int getQuantity() const { return quantity; }
    QString getUtility() const { return utility; }
};

#endif // EQUIPMENT_H