#include "employe.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>

employe::employe(const QString& nom, const QString& prenom, const QString& mail, const QString& mot_de_passe, int num_tel, const QString& adresse, const QString& genre)
    : nom(nom), prenom(prenom), mail(mail), mot_de_passe(mot_de_passe), num_tel(num_tel), adresse(adresse), genre(genre)
{
}

employe::employe() {}
// afficher employe
QSqlQueryModel* employe::afficherEmploye() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur requête:" << model->lastError().text();
    } else {
        qDebug() << model->rowCount() << "**** enregistrements trouvés******";
    }

    return model;
}

// Supprimer employe
bool employe::supprimerEmploye(int idemp) {
    QSqlQuery query;
    query.prepare("DELETE FROM employe WHERE id_emp = :id_emp");
    query.bindValue(":id_emp", idemp);

    if (!query.exec()) {
        qDebug() << "Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
    return true;
}

// Modifier employe
bool employe::modifierEmploye(int id_emp, const QString& nom, const QString& prenom, const QString& mail, const QString& mot_de_passe, int num_tel, const QString& adresse, const QString& genre) // Updated to include genre
{
    QSqlQuery query;
    query.prepare("UPDATE employe SET nom = :nom, prenom = :prenom, mail = :mail, "
                  "mot_de_passe = :mot_de_passe, num_tel = :num_tel, adresse = :adresse, genre = :genre WHERE id_emp = :id_emp");

    query.bindValue(":id_emp", id_emp);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":mail", mail);
    query.bindValue(":mot_de_passe", mot_de_passe);
    query.bindValue(":num_tel", num_tel);
    query.bindValue(":adresse", adresse);
    query.bindValue(":genre", genre); // Bind the genre value

    if (!query.exec()) {
        qDebug() << "Erreur lors de la mise à jour:" << query.lastError().text();
        return false;
    }
    return true;
}

// Ajouter employe
bool employe::ajouterEmploye(employe p) {
    QSqlQuery query;
    query.prepare("INSERT INTO employe (nom, prenom, mail, mot_de_passe, num_tel, adresse, genre) "
                  "VALUES (:nom, :prenom, :mail, :mot_de_passe, :num_tel, :adresse, :genre)"); // Include genre in the insert statement

    query.bindValue(":nom", p.nom);
    query.bindValue(":prenom", p.prenom);
    query.bindValue(":mail", p.mail);
    query.bindValue(":mot_de_passe", p.mot_de_passe);
    query.bindValue(":num_tel", p.num_tel);
    query.bindValue(":adresse", p.adresse);
    query.bindValue(":genre", p.genre); // Bind the genre value

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion:" << query.lastError().text();
        return false;
    }
    return true;
}

// recherche par nom
QSqlQueryModel* employe::rechercheparnom(const QString& recherche) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM employe WHERE nom LIKE :recherche");

    query.bindValue(":recherche", "%" + recherche + "%");

    if (query.exec()) {
        model->setQuery("SELECT * FROM employe WHERE nom LIKE :recherche");
    } else {
        qDebug() << "Query execution failed: " << query.lastError().text();
    }

    return model;
}

// tri ascendant par nom
QSqlQueryModel* employe::trieparnom() {
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe ORDER BY nom ASC");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur de tri" << model->lastError().text();
    }
    return model;
}
