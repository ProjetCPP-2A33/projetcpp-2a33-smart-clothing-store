#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client {
<<<<<<< HEAD
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
=======

private:
    int id_client;
    QString photoPath;  // Store the path to the image

public:
    // Attributes for the client
    int id_clients;
    QString nom;
    QString prenom;
    QString sexe;
    int num_tel;  // Change to int
    int age;

    // Constructors
    Client(int id, const QString &nom, const QString &prenom, const QString &sexe, int num_tel, int age, const QString &imagePath = "")
        : id_clients(id), nom(nom), prenom(prenom), sexe(sexe), num_tel(num_tel), age(age) {}

    Client() : id_clients(0), num_tel(0), age(0) {}

    // Getter and Setter for id_clients
    int getIdClients() const { return id_clients; }
    void setIdClients(int id) { id_clients = id; }

    // Getter and Setter for num_tel
    void setNumTel(int num) { num_tel = num; }

    // Getter and Setter for age
    void setAge(int a) { age = a; }

    // Getter and Setter for imagePath
    static QList<Client> getAllClients();
     void setPhotoPath(const QString &path);
     QString getPhotoPath() const;

>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)

    // CRUD Operations
    bool create();
    QSqlQueryModel *afficher();
    bool read(int id);
    bool update();
    bool deleteClient(int id);
    void on_searchTextChanged(const QString &text);
    QSqlQueryModel* search(const QString& searchTerm);
    QSqlQueryModel* trierParNom();
<<<<<<< HEAD
   QSqlQueryModel* trierParNom(bool ordreDescendant);
QPair<int, int> getSexeStatistics();

QSqlQueryModel* getStatistics();


};
=======
    QSqlQueryModel* trierParNom(bool ordreDescendant);
    QPair<int, int> getSexeStatistics();
    bool updateImagePath(int clientId);
    QSqlQueryModel* getStatistics();

    // Searching by photo path
    QSqlQueryModel* searchByPhotoPath(const QString& path);
    bool updateImage();
QSqlQueryModel* rechercherParImage(const QString &photoPath);

};

>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
#endif // CLIENT_H
