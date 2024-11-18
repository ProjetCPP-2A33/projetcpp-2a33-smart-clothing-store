#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientswindow.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include "client.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    buttonArticle = new QPushButton("Article", this);
    buttonClients = new QPushButton("Clients", this);
    buttonCommandes = new QPushButton("Commandes", this);
    buttonEmployes = new QPushButton("Employés", this);
    buttonFournisseurs = new QPushButton("Fournisseurs", this);
    buttonEquipements = new QPushButton("Équipements", this);
    buttonQuitter = new QPushButton("Quitter", this);

    int buttonWidth = 291;
    int buttonHeight = 41;

    buttonArticle->setGeometry(870, 180, buttonWidth, buttonHeight);
    buttonClients->setGeometry(870, 240, buttonWidth, buttonHeight);
    buttonCommandes->setGeometry(870, 300, buttonWidth, buttonHeight);
    buttonEmployes->setGeometry(870, 360, buttonWidth, buttonHeight);
    buttonFournisseurs->setGeometry(870, 420, buttonWidth, buttonHeight);
    buttonEquipements->setGeometry(870, 480, buttonWidth, buttonHeight);
    buttonQuitter->setGeometry(870, 600, buttonWidth, buttonHeight);

    // Apply button styles
    QString buttonStyle = "QPushButton {"
                          "background-color: rgb(0,241, 177, 100);"
                          "color: black;"
                          "border: 2px solid lightgreen;"
                          "border-radius: 10px;"
                          "font-family: 'Segoe UI Black';"
<<<<<<< HEAD
                          "font-size: 14px;}"
                          "QPushButton:hover {"
                          "background-color: rgb(140, 170, 170);}"
=======
                          "font-size: 19px;}"
                          "QPushButton:hover {"
                          "background-color: rgb(219, 254, 212);}"
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
                          "QPushButton:pressed {"
                          "background-color: lightgreen;}";

    // Set styles for buttons
    for (auto button : {buttonArticle, buttonClients, buttonCommandes, buttonEmployes, buttonFournisseurs, buttonEquipements, buttonQuitter}) {
        button->setStyleSheet(buttonStyle);
    }

    // Connect signals to respective slots
    connect(buttonClients, &QPushButton::clicked, this, &MainWindow::openClientsWindow);
    connect(buttonQuitter, &QPushButton::clicked, this, &MainWindow::closeApplication);
}

void MainWindow::openClientsWindow() {
    ClientsWindow *clientsWindow = new ClientsWindow(this);
<<<<<<< HEAD
       clientsWindow->move(this->x(), this->y());

       Client client;
       QSqlQueryModel *model = client.afficher();  // Get model from client
       clientsWindow->setTableViewModel(model);    // Use the public function to set the model

       clientsWindow->show();

       // Appeler la méthode publique qui appelle 'on_pushButton_clients_clicked'
       clientsWindow->afficherStatistiques(); // Afficher les statistiques
=======
        clientsWindow->move(this->x(), this->y());  // Position the new window

        Client client;
        QSqlQueryModel *model = client.afficher();  // Get model from client
        clientsWindow->setTableViewModel(model);    // Set model in ClientsWindow

        clientsWindow->show();

        // Optionally call a method to show statistics or other actions
        clientsWindow->afficherStatistiques(); // Show statistics if needed
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
}

void MainWindow::closeApplication() {
    QApplication::quit(); // Close the application when the "Quitter" button is clicked
}

MainWindow::~MainWindow() {
    delete ui;
}
