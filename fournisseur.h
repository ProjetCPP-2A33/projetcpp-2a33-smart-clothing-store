#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPainter>

class fournisseur
{

public:
    fournisseur();
    fournisseur(int id, QString nom, QString telephone, QString produitfournis, QString datecollaboration, QString adresse, float materiauxRecycles, float empreinteCarbone, QString rfidId);

    int getID() const;
    QString getNom() const;
    QString getTelephone() const;
    QString getProduitfournis() const;
    QString getDatecollaboration() const;
    QString getAdresse() const;
    float getMateriauxRecycles() const;
    float getEmpreinteCarbone() const;
    QString getRfidId() const;
    bool estDurable() const;  // Ajoutez cette ligne

    void setID(int id);
    void setNom(const QString &nom);
    void setTelephone(const QString &telephone);
    void setProduitfournis(const QString &produitfournis);
    void setDatecollaboration(const QString &datecollaboration);
    void setAdresse(const QString &adresse);
    void setMateriauxRecycles(float materiauxRecycles);
    void setEmpreinteCarbone(float empreinteCarbone);
    void setRfidId(const QString &rfidId);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int id);
    bool exporterPDF(const QString &nomFichier, QAbstractItemModel *model);
    bool chercherParID(int id,fournisseur &result);
    QSqlQueryModel* trierParID(bool asc);
    bool chargerFournisseurParId(int id);  // Récupère les données du fournisseur par son ID
    float calculerDurabilite() const;
    QMap<QString, int> statistiquesFournisseur();
    bool modifier(int id);




private:
    int id;
    QString nom;
    QString telephone;
    QString produitfournis;
    QString datecollaboration;
    QString adresse;
    float materiauxRecycles; // Pourcentage de matériaux recyclés
    float empreinteCarbone;  // Empreinte carbone en CO2
      QString rfidId;  // Added RFID ID member variable
};

#endif // FOURNISSEUR_H
