#include "clientswindow.h"
#include "ui_clientswindow.h"

#include "ajoutewindow.h"
#include "supprimewindow.h"
#include "modifierwindow.h"
#include "parametreswindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>

ClientsWindow::ClientsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientsWindow),
    activeButton(nullptr) // Initialiser activeButton à nullptr
{
    ui->setupUi(this);
    setWindowTitle("Clients");
 ////////////////////////////////////////////////////////////
 ///

    // Créer le tableau
    QTableWidget* tableWidget = new QTableWidget(this);
    tableWidget->setGeometry(240, 150, 600, 200); // Position et taille du tableau

    // Définir le nombre de lignes et de colonnes
    tableWidget->setRowCount(5);  // Exemple : 5 lignes
    tableWidget->setColumnCount(3); // Exemple : 3 colonnes

    // Définir les en-têtes des colonnes
    QStringList headers;
    headers << "Nom" << "Prénom" << "Âge"; // Remplacez par vos propres en-têtes
    tableWidget->setHorizontalHeaderLabels(headers);

    // Remplir le tableau avec des données d'exemple


    // Créer les boutons
    QPushButton* buttonAccueil = new QPushButton("Accueil", this);
    buttonAccueil->setGeometry(20, 170, 175, 45);

    // Ajouter une icône au bouton
    QIcon iconAccueil(":/image33/ima.png"); // Assurez-vous que le chemin vers l'image est correct
    buttonAccueil->setIcon(iconAccueil);
    buttonAccueil->setIconSize(QSize(70, 40)); // Ajuster la taille de l'icône

    QPushButton* buttonAjoute = new QPushButton("Ajoute", this);
    buttonAjoute->setGeometry(20, 260, 175, 45);
    QIcon iconAjoute(":/image33/tt1.png");
    buttonAjoute->setIcon(iconAjoute);
    buttonAjoute->setIconSize(QSize(60, 30));

    QPushButton* buttonSupprime = new QPushButton("Supprime", this);
    buttonSupprime->setGeometry(20, 350, 175, 45);
    QIcon iconSupprime(":/image33/rrr1.png");
    buttonSupprime->setIcon(iconSupprime);
    buttonSupprime->setIconSize(QSize(60, 30));

    QPushButton* buttonModifier = new QPushButton("Modifier", this);
    buttonModifier->setGeometry(20, 440, 175, 45);
    QIcon iconModifier(":/image33/rr33.png");
    buttonModifier->setIcon(iconModifier);
    buttonModifier->setIconSize(QSize(60, 30));

    QPushButton* buttonParametres = new QPushButton("Paramètres", this);
    buttonParametres->setGeometry(20, 530, 175, 45);
    QIcon iconParametres(":/image33/222.png");
    buttonParametres->setIcon(iconParametres);
    buttonParametres->setIconSize(QSize(60, 30));

    // Créer le bouton Retour
    QPushButton* buttonRetour = new QPushButton("Retour", this);
    buttonRetour->setGeometry(15, 730, 175, 41);
    QIcon iconRetour(":/image33/1723873.png");
    buttonRetour->setIcon(iconRetour);
    buttonRetour->setIconSize(QSize(60, 30));

    // Définir la feuille de style pour tous les boutons
    QString buttonStyle =
        "QPushButton {"
        "    font-family: 'Segoe UI Black';"
        "    font-size: 14px;"
        "    background-color: white;"
        "    color: black;"
        "    border: 2px solid lightgreen;"
        "    border-radius: 19px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgb(240, 220, 170);"
        "}"
        "QPushButton:pressed {"
        "    background-color: lightgreen;"
        "}";

    // Appliquer le style à chaque bouton
    buttonAccueil->setStyleSheet(buttonStyle);
    buttonAjoute->setStyleSheet(buttonStyle);
    buttonSupprime->setStyleSheet(buttonStyle);
    buttonModifier->setStyleSheet(buttonStyle);
    buttonParametres->setStyleSheet(buttonStyle);
    buttonRetour->setStyleSheet(buttonStyle); // Appliquer le style au bouton Retour

    // Connecter les boutons à leurs fonctions respectives
    connect(buttonAjoute, &QPushButton::clicked, this, &ClientsWindow::showAjoute);
    connect(buttonSupprime, &QPushButton::clicked, this, &ClientsWindow::showSupprime);
    connect(buttonModifier, &QPushButton::clicked, this, &ClientsWindow::showModifier);
    connect(buttonParametres, &QPushButton::clicked, this, &ClientsWindow::showParametres);
    connect(buttonRetour, &QPushButton::clicked, this, &ClientsWindow::handleRetour);

    // Connecter les boutons à la fonction de gestion de clic
    connect(buttonAccueil, &QPushButton::clicked, this, [=]() { handleButtonClick(buttonAccueil); });
    connect(buttonAjoute, &QPushButton::clicked, this, [=]() { handleButtonClick(buttonAjoute); });
    connect(buttonSupprime, &QPushButton::clicked, this, [=]() { handleButtonClick(buttonSupprime); });
    connect(buttonModifier, &QPushButton::clicked, this, [=]() { handleButtonClick(buttonModifier); });
    connect(buttonParametres, &QPushButton::clicked, this, [=]() { handleButtonClick(buttonParametres); });
}

void ClientsWindow::handleButtonClick(QPushButton* clickedButton) {
    // Si un bouton était déjà actif, réinitialiser son style
    if (activeButton) {
        activeButton->setStyleSheet(
            "QPushButton {"
            "    font-family: 'Segoe UI Black';"
            "    font-size: 14px;"
            "    background-color: white;"
            "    color: black;"
            "    border: 2px solid lightgreen;"
            "    border-radius: 19px;"
            "}"
            "QPushButton:hover {"
            "    background-color: rgb(240, 220, 170);"
            "}"
            "QPushButton:pressed {"
            "    background-color: lightgreen;"
            "}"
        );
    }

    // Mettre à jour le style du bouton cliqué
    clickedButton->setStyleSheet(
        "QPushButton {"
        "    font-family: 'Segoe UI Black';"
        "    font-size: 14px;"
        "    background-color: lightgreen;"
        "    color: black;"
        "    border: 2px solid lightgreen;"
        "    border-radius: 19px;"
        "}"
    );

    // Mettre à jour le bouton actif
    activeButton = clickedButton;
}

// Fonctions pour afficher d'autres fenêtres
void ClientsWindow::showAjoute() {
    AjouteWindow* ajoute = new AjouteWindow();
    ajoute->show();
}

void ClientsWindow::showSupprime() {
    SupprimeWindow* supprime = new SupprimeWindow();
    supprime->show();
}

void ClientsWindow::showModifier() {
    ModifierWindow* modifier = new ModifierWindow();
    modifier->show();
}

void ClientsWindow::showParametres() {
    ParametresWindow* parametres = new ParametresWindow();
    parametres->show();
}

// Slot pour fermer la fenêtre Clients et revenir à la fenêtre principale
void ClientsWindow::handleRetour() {
    this->close(); // Ferme la fenêtre ClientsWindow
}

ClientsWindow::~ClientsWindow() {
    delete ui;
}
