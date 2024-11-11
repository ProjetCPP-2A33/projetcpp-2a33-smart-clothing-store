#include "client.h"
#include <QSqlError>
#include <QDebug>

// Create
bool Client::create() {
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (ID_CLIENTS, NOM, PRENOM, SEXE, NUM_TEL, AGE) "
                  "VALUES (:id_clients, :nom, :prenom, :sexe, :num_tel, :age)");

    query.bindValue(":id_clients", id_clients);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":sexe", sexe);
    query.bindValue(":num_tel", num_tel); // No change needed here
    query.bindValue(":age", age);

    if (!query.exec()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        return false; // Return false if the execution failed
    }

    return true; // Return true if the execution succeeded
}

// Read
bool Client::read(int id) {
     //bache ithess basse donnnes
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE ID_CLIENTS = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        id_clients = query.value("ID_CLIENTS").toInt();
        nom = query.value("NOM").toString();
        prenom = query.value("PRENOM").toString();
        sexe = query.value("SEXE").toString();
        num_tel = query.value("NUM_TEL").toInt(); // Change to toInt()
        age = query.value("AGE").toInt(); // Change to toInt()
        return true;
    }

    qDebug() << "SQL Error:" << query.lastError().text(); // Log error if reading fails
    return false;
}

// Display
QSqlQueryModel* Client::afficher() {
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT");
    QSqlQueryModel *model = new QSqlQueryModel();

    if (!query.exec()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        delete model; // Avoid memory leak if query fails
        return nullptr; // Return nullptr on error
    }

    model->setQuery(query); // Set the query to the model
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENTS"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("AGE"));

    return model; // Return the model
}

// mofifer
bool Client::update() {
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM = :nom, PRENOM = :prenom, SEXE = :sexe, "
                  "NUM_TEL = :num_tel, AGE = :age WHERE ID_CLIENTS = :id");
    query.bindValue(":id", id_clients);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":sexe", sexe);
    query.bindValue(":num_tel", num_tel); // No change needed here
    query.bindValue(":age", age);

    if (!query.exec()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        return false; // Return false if the execution failed
    }

    return true; // Return true if the execution succeeded
}

// Delete
bool Client::deleteClient(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE ID_CLIENTS = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        return false; // Return false if the execution failed
    }

    return true; // Return true if the execution succeeded
}



QSqlQueryModel* Client::search(const QString& searchTerm) {
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE NOM LIKE :searchTerm OR PRENOM LIKE :searchTerm OR ID_CLIENTS LIKE :searchTerm");
    query.bindValue(":searchTerm", "%" + searchTerm + "%");

    QSqlQueryModel *model = new QSqlQueryModel();

    if (!query.exec()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENTS"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("AGE"));

    return model;
}

QSqlQueryModel* Client::trierParNom() {
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT ORDER BY NOM ASC"); // Trier par NOM

    QSqlQueryModel *model = new QSqlQueryModel();

    if (!query.exec()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENTS"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("AGE"));

    return model;
}


QSqlQueryModel* Client::trierParNom(bool ordreDescendant) {
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM CLIENT ORDER BY NOM %1")
                  .arg(ordreDescendant ? "DESC" : "ASC"));

    QSqlQueryModel *model = new QSqlQueryModel();

    if (!query.exec()) {
        qDebug() << "SQL Error:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENTS"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("SEXE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("AGE"));

    return model;
}


QPair<int, int> Client::getSexeStatistics() {
    QSqlQuery query;
    query.prepare("SELECT SEXE, COUNT(*) FROM CLIENT GROUP BY SEXE");

    int maleCount = 0;
    int femaleCount = 0;

    if (query.exec()) {
        while (query.next()) {
            QString sexe = query.value(0).toString();
            int count = query.value(1).toInt();

            if (sexe == "Homme") {
                maleCount = count;
            } else if (sexe == "Femme") {
                femaleCount = count;
            }
        }
    } else {
        qDebug() << "SQL Error:" << query.lastError().text();
    }

    return qMakePair(maleCount, femaleCount); // Retourne le nombre d'hommes et de femmes
}


