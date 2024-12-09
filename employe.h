#ifndef PRODUITS_H
#define PRODUITS_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QList>
#include <QDate>

class employe
{
private:
    int id_emp;
    QString nom;
    QString prenom;
    QString mail;
    QString mot_de_passe;
    int num_tel;
    QString adresse;
    QString genre; // New member variable for genre

public:
    employe();
    employe(const QString& nom, const QString& prenom, const QString& mail, const QString& mot_de_passe, int num_tel, const QString& adresse, const QString& genre);

    // Getters
    QString getNom() const { return nom; }
    QString getMail() const { return mail; }
    QString getMotDePasse() const { return mot_de_passe; }
    int getNumTel() const { return num_tel; }
    QString getAdresse() const { return adresse; }
    QString getPrenom() const { return prenom; }
    QString getGenre() const { return genre; } // New getter for genre

    // Setters
    void setNom(const QString& nm) { nom = nm; }
    void setMail(const QString& email) { mail = email; }
    void setMotDePasse(const QString& mdp) { mot_de_passe = mdp; }
    void setPrenom(const QString& pr) { prenom = pr; }
    void setAdresse(const QString& ad) { adresse = ad; }
    void setNumTel(int nmt) { num_tel = nmt; }
    void setGenre(const QString& g) { genre = g; } // New setter for genre

    // CRUD
    bool ajouterEmploye(employe p);
    QSqlQueryModel* afficherEmploye();
    bool supprimerEmploye(int id_emp);
    bool modifierEmploye(int id_emp, const QString& nom, const QString& prenom, const QString& mail, const QString& mot_de_passe, int num_tel, const QString& adresse, const QString& genre); // Updated to include genre
    QList<employe> retrouverListEmployes();
    QSqlQueryModel* rechercheparnom(const QString& recherche);
    QSqlQueryModel* trieparnom();
};

#endif // PRODUITS_H
