#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QString>
#include <QDateTime>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDate>

class historique
{
private:
    int ID_ACTION;
    QDateTime DATE_ACTION;
    QString TYPE_ACTION;
    QString DETAILS;

public:
    historique();
    historique(int ID_ACTION , QDateTime DATE_ACTION, QString TYPE_ACTION, QString DETAILS)
    {
        this->ID_ACTION = ID_ACTION;
        this->DATE_ACTION = DATE_ACTION;
        this->TYPE_ACTION = TYPE_ACTION;
        this->DETAILS = DETAILS;
    }

    // Setters
    void setID_ACTION(int i) { ID_ACTION = i; }
    void setDATE_ACTION(QDateTime h) { DATE_ACTION = h; }
    void setTYPE_ACTION(QString g) { TYPE_ACTION = g; }
    void setDETAILS(QString k) { DETAILS = k; }

    // Getters
    int getID_ACTION() const { return ID_ACTION; }
    QDateTime getDATE_ACTION() const { return DATE_ACTION; }
    QString getTYPE_ACTION() const { return TYPE_ACTION; }
    QString getDETAILS() const { return DETAILS; }

    bool Ajouterhistorique();
    QSqlQueryModel *Afficherhistorique();
};

#endif // HISTORIQUE_H
