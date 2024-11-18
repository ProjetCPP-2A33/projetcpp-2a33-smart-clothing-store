#include "client.h"
#include <QSqlError>
#include <QDebug>
<<<<<<< HEAD
=======
#include <QSqlQuery>
#include <QPixmap>

>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)

// Create
bool Client::create() {
    QSqlQuery query;
<<<<<<< HEAD
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
=======
        query.prepare("INSERT INTO CLIENT (ID_CLIENTS, NOM, PRENOM, SEXE, NUM_TEL, AGE, PHOTO) "
                      "VALUES (:id_clients, :nom, :prenom, :sexe, :num_tel, :age, :photo)");

        query.bindValue(":id_clients", id_clients);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":sexe", sexe);
        query.bindValue(":num_tel", num_tel);
        query.bindValue(":age", age);
        query.bindValue(":photo", photoPath);  // Enregistrez le chemin de l'image

        if (!query.exec()) {
            qDebug() << "SQL Error:" << query.lastError().text();
            return false;
        }

        return true;
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
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
<<<<<<< HEAD
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
=======
        query.prepare("SELECT * FROM CLIENT");

        QSqlQueryModel *model = new QSqlQueryModel();

        if (!query.exec()) {
            qDebug() << "SQL Error:" << query.lastError().text();
            delete model;
            return nullptr;
        }

        model->setQuery(query);  // Définir la requête dans le modèle

        // Définir les en-têtes de colonnes
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CLIENTS"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("SEXE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("AGE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUM_TEL"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("PHOTO"));

        // Ajouter un QPixmap dans la colonne PHOTO après que la requête ait chargé les données
        for (int row = 0; row < model->rowCount(); ++row) {
            QString imagePath = model->data(model->index(row, 6)).toString();  // Récupérer le chemin de l'image
            QPixmap pixmap(imagePath);

            if (!pixmap.isNull()) {
                model->setData(model->index(row, 6), pixmap, Qt::DecorationRole);  // Remplacer le chemin par un QPixmap
            }
        }

        return model;
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
}

// mofifer
bool Client::update() {
    QSqlQuery query;
<<<<<<< HEAD
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
=======
        query.prepare("UPDATE CLIENT SET NOM = :nom, PRENOM = :prenom, SEXE = :sexe, NUM_TEL = :num_tel, AGE = :age, PHOTO = :photo WHERE ID_CLIENTS = :id");
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":sexe", sexe);
        query.bindValue(":num_tel", num_tel);
        query.bindValue(":age", age);
        query.bindValue(":photo", photoPath);  // Lier le chemin de l'image
        query.bindValue(":id", id_clients);  // Assurez-vous que l'ID du client est correct

        return query.exec();  // Si la requête s'exécute correctement, retourne true
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
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


<<<<<<< HEAD
=======
void Client::setPhotoPath(const QString &path) {
    photoPath = path;
}

QString Client::getPhotoPath() const {
    return photoPath;
}

QList<Client> Client::getAllClients() {
    QList<Client> clients;
    QSqlQuery query("SELECT * FROM CLIENT");
    while (query.next()) {
        Client client;
        client.setIdClients(query.value(0).toInt());
        client.nom = query.value(1).toString();
        client.prenom = query.value(2).toString();
        client.sexe = query.value(3).toString();
        client.num_tel = query.value(4).toInt();
        client.age = query.value(5).toInt();
        client.setPhotoPath(query.value(6).toString());
        clients.append(client);
    }
    return clients;
}

QSqlQueryModel* Client::rechercherParImage(const QString &photoPath) {
    // Préparer une requête pour rechercher le client par image
    // Préparer une requête pour rechercher le client par image
        QSqlQuery query;
        query.prepare("SELECT ID_CLIENTS, NOM, PRENOM, SEXE, AGE, NUM_TEL FROM CLIENT WHERE PHOTO = :imagePath");
        query.bindValue(":imagePath", photoPath);

        QSqlQueryModel *model = new QSqlQueryModel();
        if (query.exec()) {
            model->setQuery(query);  // Charger les résultats dans le modèle
        } else {
            qDebug() << "Erreur lors de la recherche de l'image:" << query.lastError();
        }
        return model;
}


bool Client::updateImage()
{
    QSqlQuery query;
        query.prepare("UPDATE CLIENT SET PHOTO = :photo WHERE ID_CLIENTS = :id");
        query.bindValue(":photo", photoPath);  // Le chemin de l'image
        query.bindValue(":id", id_clients);    // L'ID du client

        return query.exec();  // Si la requête s'exécute correctement, retourne true
}

>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
