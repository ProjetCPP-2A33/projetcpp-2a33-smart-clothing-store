#include "accueilwindow.h"
#include <QVBoxLayout>
#include <QLabel>

AccueilWindow::AccueilWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Accueil");

    // Création d'un layout vertical pour la fenêtre
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Ajout d'un label pour afficher un message de bienvenue
    QLabel *welcomeLabel = new QLabel("Bienvenue dans la fenêtre d'accueil!", this);
    layout->addWidget(welcomeLabel);

    // Optionnel : Vous pouvez ajouter plus d'éléments à la fenêtre ici
    setLayout(layout);
}

AccueilWindow::~AccueilWindow() {
    // Le destructeur peut être utilisé pour libérer des ressources si nécessaire
}
