#include "commande.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

// Constructeurs
Commande::Commande() {}

Commande::Commande(int id, QDate date_creation, QString statut, int quantite, int montant_total, int id_client)
    : id(id), date_creation(date_creation), statut(statut), quantite(quantite), montant_total(montant_total), id_client(id_client) {}

Commande::Commande(QDate date_creation, QString statut, int quantite, int montant_total, int id_client)
    : date_creation(date_creation), statut(statut), quantite(quantite), montant_total(montant_total), id_client(id_client) {}

// Getters
int Commande::getID() const {
    return id;
}

QDate Commande::getDateCreation() const {
    return date_creation;
}

QString Commande::getStatut() const {
    return statut;
}

int Commande::getMontantTotal() const {
    return montant_total;
}

int Commande::getQuantite() const {
    return quantite;
}

int Commande::getClientID() const {
    return id_client;
}

// Setters
void Commande::setID(int id) {
    this->id = id;
}

void Commande::setDateCreation(QDate date_creation) {
    this->date_creation = date_creation;
}

void Commande::setStatut(QString statut) {
    this->statut = statut;
}

void Commande::setMontantTotal(int montant_total) {
    this->montant_total = montant_total;
}

void Commande::setQuantite(int quantite) {
    this->quantite = quantite;
}

void Commande::setClientID(int id_client) {
    this->id_client = id_client;
}

// Méthodes de gestion de la base de données
bool Commande::ajouter() {
    QSqlQuery query;

    // Exclude the id from the INSERT statement, let the database auto-generate it
    query.prepare("INSERT INTO commande (date_creation, statut, quantite, montant_tel, id_client) "
                  "VALUES (:date_creation, :statut, :quantite, :montant_tel, :id_client)");

    query.bindValue(":date_creation", date_creation);
    query.bindValue(":statut", statut);
    query.bindValue(":quantite", quantite);
    query.bindValue(":montant_tel", montant_total);
    query.bindValue(":id_client", id_client);

    if (!query.exec()) {
        qDebug() << "Database error:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel* Commande::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM commande ORDER BY id");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date de Création"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Montant Total"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID Client"));

    return model;
}

bool Commande::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM commande WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Commande::modifier(int id) {
    QSqlQuery query;

    query.prepare("UPDATE commande SET date_creation = :date_creation, statut = :statut, "
                  "quantite = :quantite, montant_tel = :montant_tel, id_client = :id_client WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":date_creation", date_creation);
    query.bindValue(":statut", statut);
    query.bindValue(":quantite", quantite);
    query.bindValue(":montant_tel", montant_total);  // Ensure the variable matches your field name
    query.bindValue(":id_client", id_client);

    return query.exec();
}


QSqlQueryModel* Commande::rechercherParStatut(QString terme) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Prepare the query to search by statut, date_creation, or montant_tel
    query.prepare("SELECT * FROM commande WHERE statut LIKE :terme");
    query.bindValue(":terme", "%" + terme + "%");

    // Execute the query and check for success
    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Failed to execute search query:" << query.lastError().text();
    }

    return model;
}

QSqlQueryModel* Commande::rechercherParDateCreation(QDate date_creation) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Check if the provided date is valid
    if (!date_creation.isValid()) {
        qDebug() << "Invalid date provided.";
        return model;  // Return an empty model
    }

    // Prepare the query to search by date_creation
    query.prepare("SELECT * FROM commande WHERE date_creation = :date_creation");

    // Bind the date as a QDate
    query.bindValue(":date_creation", date_creation);

    // Execute the query and set the result model
    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }

    return model;
}


QSqlQueryModel* Commande::Tri(QString cls, QString champ) {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Ensure that only valid columns and sort orders are used
    if ((champ != "date_creation" && champ != "montant_tel") ||
        (cls != "ASC" && cls != "DESC")) {
        qDebug() << "Invalid sorting parameters.";
        return model;  // Return an empty model if invalid parameters
    }

    QString queryString = "SELECT * FROM commande ORDER BY " + champ + " " + cls;
    QSqlQuery query;
    query.prepare(queryString);

    if (query.exec()) {
        model->setQuery(query);

        // Set headers for the model (adjust indices as per table structure)
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date de Création"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Statut"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr(" quantite"));

        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Montant Total"));
    } else {
        qDebug() << "Failed to execute sort query:" << query.lastError().text();
    }

    return model;
}



QBarSeries* Commande::getStatStatut() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM commande");

    // Récupérer le nombre total de commandes
    int totalCommandes = 0;
    if (query.exec() && query.next()) {
        totalCommandes = query.value(0).toInt();
    }

    if (totalCommandes == 0) {
        qDebug() << "Aucune commande trouvée pour les statistiques.";
        return nullptr;
    }

    // Préparer la requête pour compter les commandes par statut
    query.prepare("SELECT statut, COUNT(*) FROM commande GROUP BY statut");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des statistiques:" << query.lastError();
        return nullptr;
    }

    QBarSeries *series = new QBarSeries();

    // Parcourir les résultats de la requête et créer les jeux de données pour chaque statut
    while (query.next()) {
        QString statut = query.value(0).toString();
        int nombreParStatut = query.value(1).toInt();

        // Calculer le pourcentage de commandes pour chaque statut
        double pourcentage = (static_cast<double>(nombreParStatut) / totalCommandes) * 100;

        // Créer un QBarSet pour chaque statut avec le pourcentage correspondant
        QBarSet *set = new QBarSet(statut);
        *set << pourcentage;
        series->append(set);
    }

    return series;
}
