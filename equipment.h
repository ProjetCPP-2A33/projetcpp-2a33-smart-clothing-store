// equipment.h
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Equipment {
public:
    Equipment(const QString &id, const QString &name, const QString &type, int quantity, const QString &utility);

    bool ajouter(const QSqlDatabase &db);

    bool supprimer(const QSqlDatabase &db, const QString &id);

    // Attributes
    QString id;
    QString name;
    QString type;
    int quantity;
    QString utility;
};

#endif // EQUIPMENT_H
