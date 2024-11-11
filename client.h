#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client {
public:
    // Attributes
    int id_clients;
        QString nom;
        QString prenom;
        QString sexe;
        int num_tel;  // Change to int
        int age;

    // Constructor
        Client(int id, QString nom, QString prenom, QString sexe, int num_tel, int age)
                : id_clients(id), nom(nom), prenom(prenom), sexe(sexe), num_tel(num_tel), age(age) {}


    Client() : id_clients(0), num_tel(0), age(0) {}

       int getIdClients() const {
            return id_clients;
        }

        // Setter for id_clients
        void setIdClients(int id) {
            id_clients = id;
        }

        void setNumTel(int num) {
                num_tel = num;
            }

            void setAge(int a) {
                age = a;
            }

    // CRUD Operations
    bool create();
    QSqlQueryModel *afficher();
    bool read(int id);
    bool update();
    bool deleteClient(int id);
    void on_searchTextChanged(const QString &text);
    QSqlQueryModel* search(const QString& searchTerm);
    QSqlQueryModel* trierParNom();
   QSqlQueryModel* trierParNom(bool ordreDescendant);
QPair<int, int> getSexeStatistics();

QSqlQueryModel* getStatistics();


};
#endif // CLIENT_H
