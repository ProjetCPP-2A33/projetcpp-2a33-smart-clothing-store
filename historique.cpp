#include "historique.h"

historique::historique()
{

}
bool historique::Ajouterhistorique()
{
    QSqlQuery query;

    query.prepare("INSERT INTO HISTORIQUE (DATE_ACTION,TYPE_ACTION,DETAILS) "
                  "VALUES ( :DATE_ACTION ,:TYPE_ACTION ,:DETAILS )");

    //query.bindValue(":ID_ACTION", this->ID_ACTION);
    query.bindValue(":DATE_ACTION", this->DATE_ACTION);
    query.bindValue(":TYPE_ACTION", this->TYPE_ACTION);
    query.bindValue(":DETAILS", this->DETAILS);


    return query.exec();
}

QSqlQueryModel *historique::Afficherhistorique()
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    modal->setQuery("SELECT * FROM HISTORIQUE");
    modal->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_ACTION"));
    modal->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_ACTION"));
    modal->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE_ACTION"));
    modal->setHeaderData(3, Qt::Horizontal, QObject::tr("DETAILS"));



    return modal;
}
