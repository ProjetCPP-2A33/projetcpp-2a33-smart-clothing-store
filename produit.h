#ifndef PRODUIT_H
#define PRODUIT_H
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class produitData;

class produit
{
    Q_OBJECT
public:
    produit();
    produit(const produit &);
    produit &operator=(const produit &);
    ~produit();
    //constructeurs



private:
    QSharedDataPointer<produitData> data;
};

#endif // PRODUIT_H
