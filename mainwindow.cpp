#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientswindow.h" // Inclure la nouvelle fenêtre

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Créer les boutons
    buttonArticle = new QPushButton("Article", this);
    buttonClients = new QPushButton("Clients", this);
    buttonCommandes = new QPushButton("Commandes", this);
    buttonEmployes = new QPushButton("Employés", this);
    buttonFournisseurs = new QPushButton("Fournisseurs", this);
    buttonEquipements = new QPushButton("Équipements", this);
    buttonQuitter = new QPushButton("Quitter", this);

    // Définir la taille des boutons
    int buttonWidth = 291;
    int buttonHeight = 41;

    // Positionner les boutons
    buttonArticle->setGeometry(870, 180, buttonWidth, buttonHeight);
    buttonClients->setGeometry(870, 240, buttonWidth, buttonHeight);
    buttonCommandes->setGeometry(870, 300, buttonWidth, buttonHeight);
    buttonEmployes->setGeometry(870, 360, buttonWidth, buttonHeight);
    buttonFournisseurs->setGeometry(870, 420, buttonWidth, buttonHeight);
    buttonEquipements->setGeometry(870, 480, buttonWidth, buttonHeight);
    buttonQuitter->setGeometry(870, 600, buttonWidth, buttonHeight);

    // Appliquer une feuille de style pour chaque bouton
    QString buttonStyle = "QPushButton {"
                          "background-color: rgb(0,241, 177, 100);"    // Couleur de fond initiale
                          "color: black;"                // Couleur du texte par défaut
                          "border: 2px solid lightgreen;"      // Bordure
                          "border-radius: 10px;"         // Coins arrondis
                          "font-family: 'Segoe UI Black';" // Police
                          "font-size: 17px;"             // Taille de la police
                          "}"
                          "QPushButton:hover {"
                          "background-color: lightgreen;" // Couleur au survol
                          "}"
                          "QPushButton:pressed {"
                          "background-color:white ;" // Couleur lorsqu'il est pressé
                          "}";

    buttonArticle->setStyleSheet(buttonStyle);
    buttonClients->setStyleSheet(buttonStyle);
    buttonCommandes->setStyleSheet(buttonStyle);
    buttonEmployes->setStyleSheet(buttonStyle);
    buttonFournisseurs->setStyleSheet(buttonStyle);
    buttonEquipements->setStyleSheet(buttonStyle);
    buttonQuitter->setStyleSheet(buttonStyle);

    // Connecter le bouton Quitter à l'action de fermeture de l'application
    connect(buttonQuitter, &QPushButton::clicked, this, &QMainWindow::close);
      connect(buttonClients, &QPushButton::clicked, this, &MainWindow::openClientsWindow);
}
void MainWindow::openClientsWindow() {
    ClientsWindow *clientsWindow = new ClientsWindow(this);
    clientsWindow->show(); // Affiche la fenêtre Clients
}
MainWindow::~MainWindow() {
    delete ui;
}
