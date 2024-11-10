#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QBarSeries>
#include <QBarSet>
using namespace QtCharts;

class Commande {
public:
    Commande();
    Commande(int id, QDate date_creation, QString statut,int quantite, int montant_total);
    Commande(QDate date_creation, QString statut, int quantite, int montant_total);

    // Getter methods
    int getID() const;
    QDate getDateCreation() const;
    QString getStatut() const;
    int getMontantTotal() const;
    int getQuantite()const;

    // Setter methods
    void setID(int id);
    void setDateCreation(QDate date_creation);
    void setStatut(QString statut);
    void setMontantTotal(int montant_total);
    void setQuantite(int quantite);

    // Database operations
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier(int id);
    static QSqlQueryModel* rechercherParStatut(QString terme);
    QSqlQueryModel* rechercherParDateCreation(QDate date_creation);
    QSqlQueryModel* Tri(QString cls, QString champ);
    QBarSeries* getStatStatut();

private:
    int id;
    QDate date_creation;
    QString statut;
    int quantite;
    int montant_total;

};

#endif // COMMANDE_H
