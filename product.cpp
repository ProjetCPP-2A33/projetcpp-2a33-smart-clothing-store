#include "product.h"
#include <QPdfWriter>
#include <QPainter>
#include <QDebug>
#include <QSqlError>
#include "historique.h"
#include <QFile>


product::product(QString NOM_PROD,QString TAILLE_PROD,QString GENRE_PROD,QString STATUT_PROD,int ID_PROD,int PRIX_PROD)
{ this->ID_PROD=ID_PROD ;
   this->NOM_PROD=NOM_PROD;
    this->PRIX_PROD=PRIX_PROD ;
    this->STATUT_PROD=STATUT_PROD;
    this->TAILLE_PROD=TAILLE_PROD ;
    this->GENRE_PROD=GENRE_PROD ;
}
bool product ::ajouter()
{
    QSqlQuery query;
     query.prepare("INSERT INTO PRODUIT (ID_PROD, NOM_PROD, TAILLE_PROD, GENRE_PROD, STATUT_PROD, PRIX_PROD) "
                   "VALUES (:id, :nom, :taille, :genre, :statut, :prix)");
     query.bindValue(":id", ID_PROD);
     query.bindValue(":nom", NOM_PROD);
     query.bindValue(":taille", TAILLE_PROD);
     query.bindValue(":genre", GENRE_PROD);
     query.bindValue(":statut", STATUT_PROD);
     query.bindValue(":prix", PRIX_PROD);
     return query.exec();


     // Add history
     historique histo;
     histo.setDATE_ACTION(QDateTime::currentDateTime());
     histo.setTYPE_ACTION("Ajout");
     histo.setDETAILS("Un produit est ajoute: " + NOM_PROD );
     histo.Ajouterhistorique();

     // Save history to file

     QFile file("C:/Users/miriam/Desktop/projet QT/connexionBD/historique.txt");
     if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
         qDebug() << "Impossible d'ouvrir le fichier!";
         return false;
     }

     QTextStream out(&file);
     out << "Date: " << histo.getDATE_ACTION().toString() << ", Type: " << histo.getTYPE_ACTION() << ", Details: " << histo.getDETAILS() << "\n";

     file.close();
     qDebug() << "Historique est enregistré avec succes!";

     return true;
}
bool product ::supprimer(int id){
    QSqlQuery query;
       query.prepare("DELETE FROM PRODUIT WHERE ID_PROD = :id");
       query.bindValue(":id", id);
       return query.exec();


       // Add history
       historique histo;
       histo.setDATE_ACTION(QDateTime::currentDateTime());
       histo.setTYPE_ACTION("Suppression");
       histo.setDETAILS("Supprimer produit avec le nom " + NOM_PROD);
       histo.Ajouterhistorique();

       // Save history to file
       QFile file("C:/Users/adamc/Desktop/qt calendar louay/Atelier_Connexion/history.txt");
       if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
           qDebug() << "impossible d'ouvrir le fichier!";
           return false;


       }

       QTextStream out(&file);
       out << "Date: " << histo.getDATE_ACTION().toString() << ", Type: " << histo.getTYPE_ACTION() << ", Details: " << histo.getDETAILS() << "\n";

       file.close();
       qDebug() << "Historique est enregistré avec succes!";
       return true;


}
QSqlQueryModel* product::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Exécuter la requête pour récupérer toutes les données de la table 'products'
    model->setQuery("SELECT * FROM PRODUIT");

    // Ajouter des en-têtes pour les colonnes (pour une meilleure lisibilité)
    model->setHeaderData(0, Qt::Horizontal, "ID_PROD");
    model->setHeaderData(1, Qt::Horizontal, "NOM_PROD");
    model->setHeaderData(2, Qt::Horizontal, "TAILLE_PROD");
    model->setHeaderData(3, Qt::Horizontal, "GENRE_PROD");
    model->setHeaderData(4, Qt::Horizontal, "STATUT_PROD");
    model->setHeaderData(5, Qt::Horizontal, "PRIX_PROD");

    return model;


}
bool product::modifier() {
    QSqlQuery query;

    if (!query.prepare("UPDATE PRODUIT SET NOM_PROD = :NOM_PROD, TAILLE_PROD = :TAILLE_PROD, GENRE_PROD = :GENRE_PROD, STATUT_PROD = :STATUT_PROD, PRIX_PROD = :PRIX_PROD  WHERE ID_PROD = :ID_PROD")) {
        qDebug() << "Prepare failed:" << query.lastError();
        return false;
    }

    query.bindValue(":NOM_PROD", NOM_PROD);
    query.bindValue(":TAILLE_PROD", TAILLE_PROD);
    query.bindValue(":GENRE_PROD", GENRE_PROD);
    query.bindValue(":STATUT_PROD", STATUT_PROD);
    query.bindValue(":PRIX_PROD", PRIX_PROD);
    query.bindValue(":ID_PROD", ID_PROD);


    if (!query.exec()) {
        qDebug() << "Exec failed:" << query.lastError();
        return false;
    }
        return true;

}


    QSqlQueryModel* product::triparprix(bool croissant) {
        QSqlQueryModel* model = new QSqlQueryModel();
        if (croissant) {
            model->setQuery("SELECT * FROM PRODUIT ORDER BY PRIX_PROD ASC");
        } else {
            model->setQuery("SELECT * FROM PRODUIT ORDER BY PRIX_PROD DESC");
        }
        return model;
    }
    QSqlQueryModel* product::rechercherparid(int id) {
        QSqlQueryModel* model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT * FROM PRODUIT WHERE ID_PROD = :id");
        query.bindValue(":id", id);
        query.exec();
        model->setQuery(query);
        return model;
    }
    QSqlQueryModel* product::rechercherparnom(QString n) {
        QSqlQueryModel* model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT * FROM PRODUIT WHERE NOM_PROD LIKE :name");
        query.bindValue(":name", "%" + n + "%");
        query.exec();
        model->setQuery(query);
        return model;
    }
    QMap<QString, int> product::statistiquegammedeprix() {
        QSqlQuery query;
        QMap<QString, int> priceRangeCount;

        // Requête pour compter les produits par gamme de prix
        query.exec("SELECT "
                   "CASE "
                   "WHEN PRIX_PROD BETWEEN 0 AND 50 THEN '0-50' "
                   "WHEN PRIX_PROD BETWEEN 51 AND 100 THEN '51-100' "
                   "WHEN PRIX_PROD BETWEEN 101 AND 200 THEN '101-200' "
                   "WHEN PRIX_PROD BETWEEN 201 AND 500 THEN '201-500' "
                   "ELSE '500+' "
                   "END AS PriceRange, "
                   "COUNT(*) "
                   "FROM PRODUIT "
                   "GROUP BY PriceRange");

        // Parcours des résultats et ajout dans la map
        while (query.next()) {
            QString range = query.value(0).toString();
            int count = query.value(1).toInt();
            priceRangeCount[range] = count;
        }

        return priceRangeCount;
    }
    void product::exporterpdf() {
        // Création du fichier PDF
        QPdfWriter writer("produit_list.pdf");
        writer.setPageSize(QPagedPaintDevice::A4);

        // Création d'un objet QPainter pour dessiner dans le PDF
        QPainter painter(&writer);

        // Paramètres de dessin
        painter.setFont(QFont("Arial", 10));
        painter.setPen(Qt::black);

        // Titre
        painter.drawText(100, 100, "Liste des produits et leurs attributs");

        // Titre des colonnes
        painter.drawText(100, 120, "ID Produit");
        painter.drawText(200, 120, "Nom Produit");
        painter.drawText(300, 120, "Taille Produit");
        painter.drawText(400, 120, "Genre Produit");
        painter.drawText(500, 120, "Statut Produit");
        painter.drawText(600, 120, "Prix Produit");

        // Position verticale de départ
        int yOffset = 140;

        QSqlQuery query;
        query.exec("SELECT ID_PROD, NOM_PROD, TAILLE_PROD, GENRE_PROD, STATUT_PROD, PRIX_PROD FROM PRODUIT");

        // Parcours des résultats et ajout dans le PDF
        while (query.next()) {
            QString id = query.value(0).toString();
            QString name = query.value(1).toString();
            QString size = query.value(2).toString();
            QString genre = query.value(3).toString();
            QString status = query.value(4).toString();
            int price = query.value(5).toInt();

            // Dessiner les données dans le PDF
            painter.drawText(100, yOffset, id);
            painter.drawText(200, yOffset, name);
            painter.drawText(300, yOffset, size);
            painter.drawText(400, yOffset, genre);
            painter.drawText(500, yOffset, status);
            painter.drawText(600, yOffset, QString::number(price));

            // Espacement entre les lignes
            yOffset += 20;
        }

        // Fin de l'écriture dans le PDF
        painter.end();
    }

    QVector<int> product::recommendationparknn( int k) {
        QSqlQuery query;
        QVector<int> recommendations;

        // Créer un vecteur pour stocker les distances entre les produits
        QVector<QPair<int, double>> productDistances;  // Paires de (ID_PROD, distance)

        // Récupérer tous les produits dans la base de données (ou une sélection restreinte si nécessaire)
        query.prepare("SELECT ID_PROD, NOM_PROD, TAILLE_PROD, GENRE_PROD, STATUT_PROD, PRIX_PROD FROM PRODUIT");
        query.exec();

        // Comparer tous les produits entre eux (on ne filtre plus par utilisateur)
        QVector<int> allProductIds;
        while (query.next()) {
            allProductIds.append(query.value(0).toInt());
        }

        // Comparer chaque produit avec les autres produits
        for (int ratedProductId : allProductIds) {
            // Récupérer les informations du produit
            query.prepare("SELECT NOM_PROD, TAILLE_PROD, GENRE_PROD, STATUT_PROD, PRIX_PROD FROM PRODUIT WHERE ID_PROD = :ratedProductId");
            query.bindValue(":ratedProductId", ratedProductId);
            query.exec();

            query.next();
            QString ratedProductName = query.value(0).toString();
            QString ratedProductSize = query.value(1).toString();
            QString ratedProductGenre = query.value(2).toString();
            QString ratedProductStatus = query.value(3).toString();
            int ratedProductPrice = query.value(4).toInt();

            // Comparer avec les autres produits
            QSqlQuery compareQuery;
            compareQuery.prepare("SELECT ID_PROD, NOM_PROD, TAILLE_PROD, GENRE_PROD, STATUT_PROD, PRIX_PROD FROM PRODUIT WHERE ID_PROD != :ratedProductId");
            compareQuery.bindValue(":ratedProductId", ratedProductId);
            compareQuery.exec();

            while (compareQuery.next()) {
                int comparedProductId = compareQuery.value(0).toInt();
                QString comparedProductName = compareQuery.value(1).toString();
                QString comparedProductSize = compareQuery.value(2).toString();
                QString comparedProductGenre = compareQuery.value(3).toString();
                QString comparedProductStatus = compareQuery.value(4).toString();
                int comparedProductPrice = compareQuery.value(5).toInt();

                // Calcul de la distance entre les produits
                double distance = 0.0;

                // Comparer la taille des produits
                if (ratedProductSize != comparedProductSize) {
                    distance += 1.0; // Pénalité si la taille est différente
                }

                // Comparer le genre des produits (chaînes de caractères)
                if (ratedProductGenre != comparedProductGenre) {
                    distance += 1.0; // Pénalité si le genre est différent
                }

                // Comparer le statut des produits
                if (ratedProductStatus != comparedProductStatus) {
                    distance += 1.0; // Pénalité si le statut est différent
                }

                // Comparer les prix des produits
                distance += std::abs(ratedProductPrice - comparedProductPrice) / 100.0; // Normaliser la différence de prix

                // Ajouter à la liste des distances
                productDistances.append(QPair<int, double>(comparedProductId, distance));
            }
        }

        // Trier les produits en fonction de la distance (du plus proche au plus éloigné)
        std::sort(productDistances.begin(), productDistances.end(), [](const QPair<int, double>& a, const QPair<int, double>& b) {
            return a.second < b.second;  // Trier par distance croissante
        });

        // Retourner les k produits les plus proches
        for (int i = 0; i < k && i < productDistances.size(); ++i) {
            recommendations.append(productDistances[i].first);
        }

        return recommendations;
    }



