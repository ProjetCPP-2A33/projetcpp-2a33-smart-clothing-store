#ifndef PRODUCT_H
#define PRODUCT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class product//les variables li bech nst3mlhom
{ QString NOM_PROD,TAILLE_PROD,GENRE_PROD,STATUT_PROD ;
    int ID_PROD,PRIX_PROD;
public:
    //constructeurs
    product(){}
    product(QString,QString,QString,QString,int,int);
    //getters
    QString getNom(){return NOM_PROD;}
    QString gettaille(){return TAILLE_PROD;}
    QString getgenre(){return GENRE_PROD;}
    QString getstatut(){return STATUT_PROD;}
    int getid(){return ID_PROD;}
    int getprix(){return PRIX_PROD;}
    //SETTERS
    void setnom(QString n){NOM_PROD=n;}
    void settaille(QString t){TAILLE_PROD=t;}
    void setgenre(QString g){GENRE_PROD=g;}
    void setstatut(QString s){STATUT_PROD=s;}
    void setid(int id){this->ID_PROD=id;}
    void setprix(int p){PRIX_PROD=p;}
    //Fonctionnalites de base n7ot les fonctions li bech nst3mlhom
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel*triparprix(bool croissant);
    QSqlQueryModel*rechercherparid(int id);
    QSqlQueryModel*rechercherparnom(QString n) ;
    QMap<QString,int>statistiquegammedeprix();
    void exporterpdf();
    QVector<int>recommendationparknn(int k);
};

#endif // PRODUCT_H
