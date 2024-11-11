#include "clientswindow.h"
#include "ui_clientswindow.h"
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "client.h"
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QPageLayout>
#include <QTableView>
#include <QHeaderView>
#include <QGraphicsEllipseItem>  // Ajoutez cette ligne
#include <QGraphicsScene>

ClientsWindow::ClientsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientsWindow)  // Initialize the ui pointer correctly
{

    ui->setupUi(this);  // This should now work properly
    this->move(0, 0);  // Positionner la fenêtre à (0, 0)
        scene = new QGraphicsScene();
        ui->graphicsView->setScene(scene);  //
    ui->id->setValidator(new QIntValidator(0, 999999, this)); // ID validator
    ui->age->setValidator(new QIntValidator(0, 50, this));  // Age validator (assuming age <= 50)
    ui->numtel->setValidator(new QIntValidator(100000000, 999999999, this)); // Phone number validator (9 digits)

    // Utilisation de QRegularExpressionValidator pour valider les champs texte
    ui->nom->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-zàâçéèêëîïôûùüÿ]+( [A-Za-zàâçéèêëîïôûùüÿ]+)*"), this));  // Nom
    ui->prenom->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-zàâçéèêëîïôûùüÿ]+( [A-Za-zàâçéèêëîïôûùüÿ]+)*"), this));  // Prénom
   connect(ui->trierButton, &QPushButton::clicked, this, &ClientsWindow::on_trierParNom_clicked);
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(updateIdField()));
  connect(ui->rechercheLineEdit, &QLineEdit::textChanged, this, &ClientsWindow::on_recherche_textChanged);
connect(ui->exportButton, &QPushButton::clicked, this, &ClientsWindow::exporterPDF);

connect(ui->pushButton, &QPushButton::clicked, this, &ClientsWindow::on_pushButton_clients_clicked);
    // Créer les boutons

    QPushButton* buttonRetour = new QPushButton("Retour", this);

    // Définir la géométrie des boutons

    buttonRetour->setGeometry(15, 630, 175, 41);

    // Définir les icônes des boutons

    buttonRetour->setIcon(QIcon(":/image/1723873.png"));
    buttonRetour->setIconSize(QSize(60, 30));

    // Définir les styles des boutons
    QString buttonStyle =
        "QPushButton {"
        "    font-family: 'Segoe UI Black';"
        "    font-size: 14px;"
        "    background-color: white;"
        "    color: black;"
        "    border: 2px solid lightgreen;"
        "    border-radius: 19px;"
        "} "
        "QPushButton:hover {"
        "    background-color: rgb(240, 220, 170);"
        "} "
        "QPushButton:pressed {"
        "    background-color: lightgreen;"
        "}";



    // Connecter les signaux aux slots
    connect(buttonRetour, &QPushButton::clicked, this, &ClientsWindow::handleRetour);

}

void ClientsWindow::handleButtonClick(QPushButton* clickedButton) {
    if (activeButton) {
        activeButton->setStyleSheet(
            "QPushButton {"
            "    font-family: 'Segoe UI Black';"
            "    font-size: 14px;"
            "    background-color: white;"
            "    color: black;"
            "    border: 2px solid lightgreen;"
            "    border-radius: 19px;"
            "} "
            "QPushButton:hover {"
            "    background-color: rgb(240, 220, 170);"
            "} "
            "QPushButton:pressed {"
            "    background-color: lightgreen;"
            "}");
    }
    clickedButton->setStyleSheet(
        "QPushButton {"
        "    font-family: 'Segoe UI Black';"
        "    font-size: 14px;"
        "    background-color: lightgreen;"
        "    color: black;"
        "    border: 2px solid lightgreen;"
        "    border-radius: 19px;"
        "}");
    activeButton = clickedButton;
}

void ClientsWindow::handleRetour() {
    this->close();  // Fermer la fenêtre ClientsWindow lorsque "Retour" est cliqué
}






ClientsWindow::~ClientsWindow() {
    delete ui;  // Libérer la mémoire de l'UI
}

void ClientsWindow::on_pushButton_5_clicked()
{
     Client m1;

     ui->stackedWidget->setCurrentWidget(ui->page_4);
      ui->tableView_2->setModel(m1.afficher());
       refreshAllTablesAndViews();
}
void ClientsWindow::on_pushButton_2_clicked()
{
   Client m1;

   ui->stackedWidget->setCurrentWidget(ui->page_2);
    ui->tableView->setModel(m1.afficher());
   refreshAllTablesAndViews();
   ui->graphicsView->setScene(scene);
}

void ClientsWindow::on_pushButton_3_clicked()
{
    Client m1;

    ui->stackedWidget->setCurrentWidget(ui->page_3);
    ui->tableView->setModel(m1.afficher());
     refreshAllTablesAndViews();
}

void ClientsWindow::on_pushButton_4_clicked()
{
    Client m1;

    ui->stackedWidget->setCurrentWidget(ui->page_4);
      ui->tableView->setModel(m1.afficher());
       refreshAllTablesAndViews();
}


void ClientsWindow::on_pushButton_clicked()
{
     Client m1;
      ui->stackedWidget->setCurrentWidget(ui->page);
      ui->tableView->setModel(m1.afficher());

}


void ClientsWindow::on_pushButton_8_clicked()
{
    Client m1;
     ui->stackedWidget->setCurrentWidget(ui->page);
      ui->tableView_2->setModel(m1.afficher());
}


void ClientsWindow::on_pushButton_7_clicked()
{
    Client m1;

    ui->stackedWidget->setCurrentWidget(ui->page_3);
    ui->tableView_2->setModel(m1.afficher());
}


void ClientsWindow::on_pushButton_10_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page_2);
     ui->tableView_3->setModel(m1.afficher());
}


void ClientsWindow::on_pushButton_13_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page);

    ui->tableView_3->setModel(m1.afficher());
}


void ClientsWindow::on_pushButton_15_clicked()
{
    Client m1;
     ui->stackedWidget->setCurrentWidget(ui->page);
     ui->tableView_4->setModel(m1.afficher());
}


void ClientsWindow::on_pushButton_17_clicked()
{
    Client m1;

     ui->stackedWidget->setCurrentWidget(ui->page_2);
       ui->tableView_4->setModel(m1.afficher());
}


void ClientsWindow::on_pushButton_16_clicked()
{
    Client m1;
     ui->stackedWidget->setCurrentWidget(ui->page_3);
     ui->tableView_4->setModel(m1.afficher());
}


void ClientsWindow::on_pushButton_19_clicked()
{
    Client m1;
     ui->stackedWidget->setCurrentWidget(ui->page_4);
      ui->tableView_4->setModel(m1.afficher()); // Refresh the table view
}


void ClientsWindow::on_pushButton_6_clicked()
{
      Client m1;
      ui->stackedWidget->setCurrentWidget(ui->page_2);
      ui->tableView_2->setModel(m1.afficher()); // Refresh the table view
}


void ClientsWindow::on_pushButton_14_clicked()
{Client m1;
     ui->stackedWidget->setCurrentWidget(ui->page_4);
     ui->tableView_3->setModel(m1.afficher()); // Refresh the table view
}


void ClientsWindow::on_pushButton_9_clicked()
{

    int id = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    int num_tel = ui->numtel->text().toInt();
    int age = ui->age->text().toInt();

    // Determine the sexe based on the selected radio button
    QString sexe;
    if (ui->homme->isChecked()) {
        sexe = "Homme";
    } else if (ui->femme->isChecked()) {
        sexe = "Femme";
    } else {
        sexe = "Autre"; // or handle this case as needed
    }

    // Now create the client with the determined sexe
    Client client(id, nom, prenom, sexe, num_tel, age);

    // Attempt to create the client in the database
    if (client.create()) {
        QMessageBox::information(this, "Success", "Client created successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to create client.");
    }

    // Optionally reset radio button selection
    ui->homme->setChecked(true);  // Set "Homme" as the default selected option

    // Refresh the view with the updated client information
    ui->tableView_2->setModel(client.afficher());
    refreshAllTablesAndViews();
}

void ClientsWindow::updateIdField()
{
    // Get the selected item from comboBox_2 (assuming it contains numbers)
    int selectedId = ui->comboBox_2->currentText().toInt();

    // Update id_6 with the selected ID
    ui->id_6->setText(QString::number(selectedId));
}

void ClientsWindow::on_pushButton_18_clicked()
{
    Client m1;
    int clientId = ui->id_6->text().toInt();
    m1.setIdClients(clientId);

    bool success = m1.deleteClient(m1.getIdClients());
    //messager box
    QMessageBox msgBox;

    if (success) {
        msgBox.setText("Suppression réussie");
        ui->tableView_2->setModel(m1.afficher()); // Refresh the table view
        ui->comboBox_2->setModel(m1.afficher()); // Refresh the combo box
    } else {
        msgBox.setText("L'identifiant n'existe pas");
    }
    ui->comboBox_2->setModel(m1.afficher());
    ui->tableView_4->setModel(m1.afficher());
    ui->id_6->clear(); // Clear the input field
    msgBox.exec(); // Show the message box
    refreshAllTablesAndViews();
}








void ClientsWindow::on_pushButton_11_clicked()
{
    // Retrieve the client ID from the combo box or another selection method
    Client client;
    client.setIdClients(ui->comboBox->currentText().toInt());

    // Get updated values from input fields
    QString nom = ui->nom_2->text();
    QString prenom = ui->prenom_2->text();
    int num_tel = ui->numtel_2->text().toInt();
    int age = ui->age_2->text().toInt();

    // Determine the updated sexe based on the selected radio button
    QString sexe;
    if (ui->homme_2->isChecked()) {  // Assuming "homme_2" and "femme_2" are the radio button names in the modify UI
        sexe = "Homme";
    } else if (ui->femme_2->isChecked()) {
        sexe = "Femme";
    } else {
        sexe = "Autre"; // Handle additional cases if needed
    }

    // Set the updated values for the client
    client.nom = nom;
    client.prenom = prenom;
    client.sexe = sexe;
    client.num_tel = num_tel;
    client.age = age;

    // Attempt to update the client in the database
    if (client.update()) {
        QMessageBox::information(this, "Success", "Client updated successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to update client.");
    }

    // Refresh the view with the updated client information
    ui->tableView_3->setModel(client.afficher()); // Refresh table view for the updated data
    ui->comboBox->setModel(client.afficher());    // Refresh combo box
    refreshAllTablesAndViews();
}




void ClientsWindow::setTableViewModel(QSqlQueryModel *model) {
    // Access the QTableView via the ui pointer
    ui->tableView->setModel(model);  // Make sure "tableView" is the correct widget name
}




void ClientsWindow::on_pushButton_12_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page_3);
    ui->tableView_3->setModel(m1.afficher()); // Refresh the table view
}



void ClientsWindow::refreshAllTablesAndViews() {
    Client client;

    // Refresh each table view with the latest data
    ui->tableView->setModel(client.afficher());
    ui->tableView_2->setModel(client.afficher());
    ui->tableView_3->setModel(client.afficher());
    ui->tableView_4->setModel(client.afficher());

    // Refresh each combo box with the latest data (if needed)
    ui->comboBox->setModel(client.afficher());
    ui->comboBox_2->setModel(client.afficher());
}

void ClientsWindow::on_recherche_textChanged(const QString &text) {
    Client client;
    QSqlQueryModel *model = client.search(text); // Use the search method in Client class

    if (model) {
        ui->tableView->setModel(model); // Assuming your table view is named 'tableView'
    }
}


void ClientsWindow::on_trierParNom_clicked() {
    Client client;
    QSqlQueryModel *model = client.trierParNom(); // Appel de la méthode pour trier par nom

    if (model) {
        ui->tableView->setModel(model); // Mettre à jour la vue avec les résultats triés
    }
}




void ClientsWindow::exporterPDF() {
    QAbstractItemModel *model = ui->tableView->model();

    if (!model) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les données du tableau.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", "", "Fichiers PDF (*.pdf)");
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter writer(fileName);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageOrientation(QPageLayout::Portrait);
    writer.setResolution(300);

    QPainter painter(&writer);
    if (!painter.isActive()) {
        qDebug() << "Erreur de création du peintre pour le PDF.";
        return;
    }

    QFont font("Arial", 15);
    painter.setFont(font);

    int xOffset = 50;   // Décalage horizontal du début du tableau
    int yOffset = 330;   // Décalage vertical du début du tableau
    int lineHeight = 150; // Hauteur de chaque ligne du tableau
    int colWidth = 330;  // Largeur de chaque colonne

    int currentY = yOffset;

    // Dessiner les en-têtes des colonnes
    for (int col = 0; col < model->columnCount(); ++col) {
        QString header = model->headerData(col, Qt::Horizontal).toString();
        painter.drawText(xOffset + col * colWidth, currentY, header);
    }

    currentY += lineHeight; // Passe à la ligne suivante après les en-têtes

    // Dessiner les données de chaque client sur une seule ligne
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString cellData = model->data(model->index(row, col)).toString();
            painter.drawText(xOffset + col * colWidth, currentY, cellData);
        }
        currentY += lineHeight;

        // Si on atteint le bas de la page, ajouter une nouvelle page
        if (currentY > writer.height() - yOffset) {
            writer.newPage();
            currentY = yOffset + lineHeight; // Reprendre après l’espace des en-têtes
            for (int col = 0; col < model->columnCount(); ++col) {
                QString header = model->headerData(col, Qt::Horizontal).toString();
                painter.drawText(xOffset + col * colWidth, yOffset, header);
            }
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Le tableau des clients a été exporté avec succès.");
}

void ClientsWindow::on_pushButton_20_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page_5);

  }





void ClientsWindow::on_pushButton_21_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}


void ClientsWindow::on_pushButton_22_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}


void ClientsWindow::on_pushButton_23_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}


void ClientsWindow::on_pushButton_24_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}


void ClientsWindow::on_pushButton_28_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}


void ClientsWindow::on_pushButton_26_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void ClientsWindow::on_pushButton_27_clicked()
{
    Client m1;
    ui->stackedWidget->setCurrentWidget(ui->page);
}



void ClientsWindow::updateSexeCycle(int maleCount, int femaleCount) {
    int total = maleCount + femaleCount;
        if (total == 0) {
            qDebug() << "Total des clients égal à zéro, aucun graphique à afficher.";
            return;  // Eviter la division par zéro
        }

        // Créez une scène pour le graphique
        QGraphicsScene *scene = new QGraphicsScene();  // Déclarez 'scene' ici
        int radius = 100;  // Rayon du cercle
        int centerX = 150; // Position X du centre
        int centerY = 150; // Position Y du centre

        // Calcul des angles pour chaque section
        qreal maleAngle = 360.0 * maleCount / total;
        qreal femaleAngle = 360.0 * femaleCount / total;

        // Dessiner l'arc pour les hommes (en bleu)
        QPainterPath malePath;
        malePath.moveTo(centerX, centerY);
        malePath.arcTo(centerX - radius, centerY - radius, 2 * radius, 2 * radius, 90, -maleAngle);
        QGraphicsPathItem *maleArc = scene->addPath(malePath, QPen(Qt::blue), QBrush(Qt::blue));

        // Dessiner l'arc pour les femmes (en rose)
        QPainterPath femalePath;
        femalePath.moveTo(centerX, centerY);
        femalePath.arcTo(centerX - radius, centerY - radius, 2 * radius, 2 * radius, 90 - maleAngle, -femaleAngle);
        QGraphicsPathItem *femaleArc = scene->addPath(femalePath, QPen(QColor("pink")), QBrush(QColor("pink")));

        // Ajouter la scène au QGraphicsView pour l'affichage
        ui->graphicsView->setScene(scene);
}

void ClientsWindow::on_pushButton_clients_clicked() {
    Client client;
       QPair<int, int> statistics = client.getSexeStatistics(); // Récupère les statistiques

       int maleCount = statistics.first;
       int femaleCount = statistics.second;

       // Affichez les résultats dans un QLabel
       QString statisticsText = QString("Hommes: %1\nFemmes: %2").arg(maleCount).arg(femaleCount);
       ui->labelSexeStats->setText(statisticsText);  // Affichez dans un QLabel

       // Vérifiez si les comptes sont valides
       if (maleCount == 0 && femaleCount == 0) {
           qDebug() << "Aucun client trouvé pour les statistiques.";
       } else {
           // Mettez à jour le graphique cyclique
           updateSexeCycle(maleCount, femaleCount);
       }
}



void ClientsWindow::afficherStatistiques() {
    on_pushButton_clients_clicked();  // Appeler la méthode privée
}
