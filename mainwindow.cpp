#include "mainwindow.h"
#include"fournisseur.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QSqlQuery>
#include <QSqlError>
#include <QtCharts/QPieSlice>
#include <QLayout>
#include <QLayoutItem>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>

#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QRandomGenerator>
#include <QSqlQueryModel>  // Ajoutez cette ligne pour utiliser QSqlQueryModel
#include <QChart>

#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QSqlRecord>

#include <QTimer>

#include <QSerialPort>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QMessageBox>

// Initialisation du port série
QSerialPort serial;
//QString rfidID;

#include <QLabel>


#include "arduino.h"  // Assurez-vous que ce fichier est inclus

// Déclaration de l'objet Arduino à l'intérieur de la classe MainWindow
Arduino arduino;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Mettre le QLabel en arrière-plan
    ui->label_2->lower(); // Assure que le QLabel est sous le QTableView

    // Remplir l'image
    ui->label_2->setScaledContents(true); // Optionnel : pour redimensionner l'image à la taille du QLabel
    // Rafraîchir l'interface pour forcer l'affichage de l'image
    ui->label_2->update();
    ui->tableView->setModel(Etmp.afficher()); // Afficher les fournisseur dans le tableau
    //pour les pdf
    connect(ui->calculerButton, &QPushButton::clicked, this, &MainWindow::on_calculerDurabilite_clicked);
    fournisseur f;
    ui->tableView->setModel(f.afficher());

    connect(ui->rechercher_idrf, &QPushButton::clicked, this, &MainWindow::on_rechercher_idrf_clicked);
    connect(arduino.getserial(), &QSerialPort::readyRead, this, &MainWindow::readSerialData);
    connect(ui->rechercher_idrf, &QPushButton::clicked, this, &MainWindow::on_rechercher_idrf_clicked);

    // Connexion Arduino
    int result = arduino.connect_arduino();
    if (result == 0) {
        // Si la connexion est réussie, vous pouvez envoyer des données
        qDebug() << "Arduino connecté avec succès.";
    } else {
        qDebug() << "Impossible de connecter à Arduino. Code d'erreur: " << result;
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
    qDebug() << "Ajouter button clicked"; // Message de débogage
    int id = ui->lineEdit_ID->text().toInt();
    QString nom = ui->lineEdit_nom->text();
    QString telephone= ui->lineEdit_telephone->text();
    QString produitfournis = ui->lineEdit_produit->text();
    QString datecollaboration = ui->lineEdit_date->text();
    QString adresse = ui->lineEdit_adresse->text();
    float materiauxRecycles = ui->materiauxLineEdit->text().toFloat();
    float empreinteCarbone = ui->carboneLineEdit->text().toFloat();



    fournisseur nouvF(id, nom, telephone, produitfournis,datecollaboration,adresse, materiauxRecycles, empreinteCarbone);

    bool test = nouvF.ajouter();

    if (test) {
        QMessageBox::information(this, tr("Succès"), tr("Le fournisseur a été ajouté avec succès."), QMessageBox::Ok);
        // Rafraîchir l'affichage dans le QTableView
        ui->tableView->setModel(nouvF.afficher());
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("L'ajout du fournisseur a échoué."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    qDebug() << "Supprimer button clicked"; // Message de débogage

    // Récupérer l'ID du fournisseur à partir du champ de saisie
    int id = ui->lineEdit_IDS->text().toInt();
    bool test = Etmp.supprimer(id);

    if (test) {
        QMessageBox::information(this, tr("Succès"), tr("Suppression effectuée."), QMessageBox::Ok);
        // Rafraîchir l'affichage dans le QTableView
        ui->tableView->setModel(Etmp.afficher());
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_10_clicked() {
    int id = ui->lineEdit_recherche->text().toInt();
    fournisseur etmp, result;

    if (etmp.chercherParID(id, result)) {
        QMessageBox::information(this, "Search Result", "Fournisseur with ID " + QString::number(id) + " exists.");

        // Mettre à jour le tableau pour n'afficher que le fournisseur trouvé
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery query;
        query.prepare("SELECT * FROM FOURNISSEURS WHERE ID = :id");
        query.bindValue(":id", id);
        query.exec();
        model->setQuery(std::move(query));

        ui->tableView->setModel(model);  // Affichage dans le tableau
    } else {
        QMessageBox::information(this, "Search Result", "Fournisseur with ID " + QString::number(id) + " does not exist.");

        // Optionnel : Vider ou réinitialiser le tableau en cas de non-trouvaille
        ui->tableView->setModel(nullptr);
    }
}




void MainWindow::on_pb_pdf_clicked()
{
    // Ouvrir une boîte de dialogue pour sélectionner le chemin de sauvegarde du PDF
    QString nomFichier = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "Fichiers PDF (*.pdf)");
    if (!nomFichier.isEmpty()) {
        fournisseur etmp;

        // Récupérer les données d'employé
        QSqlQueryModel *model = etmp.afficher();

        // Vérifier si les données existent
        if (model->rowCount() == 0) {
            QMessageBox::warning(this, "Aucune donnée", "Aucun fournisseur à exporter.");
            delete model; // Libération de la mémoire
            return;
        }

        // Exporter vers PDF
        bool exportSuccess = etmp.exporterPDF(nomFichier, model);

        // Libération de mémoire
        delete model;

        if (exportSuccess) {
            QMessageBox::information(this, "Exportation PDF", "Exportation vers PDF réussie !");
        } else {
            QMessageBox::critical(this, "Erreur d'exportation", "L'exportation vers PDF a échoué.");
        }
    }
}



void MainWindow::on_pushButton_trier_clicked()
{
    qDebug() << "Trier button clicked"; // Debug message

    // Sort the employees by ID
    bool ascending = true; // Set to false if you want to sort in descending order
    ui->tableView->setModel(Etmp.trierParID(ascending));
}



float MainWindow::calculerDurabilite(float materiauxRecycles, float empreinteCarbone)
{
    // Example sustainability calculation (You can modify this formula)
    // Durability might be based on the percentage of recycled materials and the carbon footprint
    float durabilite = (materiauxRecycles * 0.5) - (empreinteCarbone * 0.5);
    return durabilite;
}
// Méthode pour charger un fournisseur par son ID
bool MainWindow::chargerFournisseurParId(int id) {
    // Recherche basique de l'ID du fournisseur
    // Remplacer ce code par une vraie recherche dans la base de données ou autre source

    if (id == 1) {  // Exemple d'ID (remplacer par une vraie recherche)
        // Assigner l'ID du fournisseur
        Etmp.setID(id);
        return true;  // Fournisseur trouvé
    }

    // Si aucun fournisseur n'est trouvé
    return false;
}
void MainWindow::on_calculerDurabilite_clicked() {
    bool ok;
    int fournisseurId = ui->fournisseurIdLineEdit->text().toInt(&ok);

    if (!ok) {
        ui->resultLabel->setText("ID invalide");
        return;
    }

    if (Etmp.chargerFournisseurParId(fournisseurId)) {
        if (Etmp.estDurable()) {
            ui->resultLabel->setText("Fournisseur durable avec un score de " + QString::number(Etmp.calculerDurabilite(), 'f', 2) + "%");
        } else {
            ui->resultLabel->setText("Fournisseur non durable. Score : " + QString::number(Etmp.calculerDurabilite(), 'f', 2) + "%");
        }
    } else {
        ui->resultLabel->setText("Fournisseur introuvable");
    }
}


void MainWindow::on_pushButton_stats_clicked(){
    // Créez une instance de fournisseur (ou utilisez une instance existante)
    fournisseur fournisseurInstance;

    // Récupérer les statistiques de durabilité ou toute autre donnée pertinente pour les fournisseurs
    QMap<QString, int> statistiques = fournisseurInstance.statistiquesFournisseur();

    if (statistiques.isEmpty()) {
        qDebug() << "Aucune donnée pour les statistiques des fournisseurs.";
        return;
    }

    for (auto it = statistiques.begin(); it != statistiques.end(); ++it) {
        qDebug() << "Fournisseur: " << it.key() << ", Nombre: " << it.value();
    }

    // Créer la série pour le graphique
    QPieSeries *series = new QPieSeries();
    for (auto it = statistiques.begin(); it != statistiques.end(); ++it) {
        QPieSlice *slice = series->append(it.key() + ": " + QString::number(it.value()), it.value());

        // Alterner entre les couleurs
        if (series->slices().size() % 2 == 0) {
            slice->setBrush(QColor(173, 216, 230)); // Gris clair
        } else {
            slice->setBrush(QColor(152, 251, 152)); // Vert pastel
        }

        // Afficher les étiquettes
        slice->setLabelVisible(true);
    }

    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des fournisseurs par critères");
    chart->setAnimationOptions(QChart::SeriesAnimations);  // Activer les animations

    // Personnaliser le titre
    QFont titleFont;
    titleFont.setPixelSize(20); // Taille du titre
    titleFont.setBold(true);    // Gras
    titleFont.setItalic(false);
    chart->setTitleFont(titleFont);
    chart->setTitleBrush(QBrush(QColor(152, 251, 152))); // Couleur du titre (vert pastel)

    // Personnaliser les étiquettes
    QFont labelFont;
    labelFont.setPixelSize(16); // Taille des étiquettes
    for (QPieSlice *slice : series->slices()) {
        slice->setLabelFont(labelFont);
        slice->setLabelBrush(QBrush(QColor(152, 251, 152))); // Couleur des étiquettes (vert pastel)
    }

    // Créer la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Nettoyer l'ancien contenu de verticalLayout_4
    QLayoutItem *item;
    while ((item = ui->verticalLayout_4->takeAt(0)) != nullptr) {
        delete item->widget(); // Supprimer le widget
        delete item;           // Supprimer l'élément
    }

    // Ajouter le graphique au layout
    ui->verticalLayout_4->addWidget(chartView);

    // Afficher un message dans la console de débogage pour confirmer la mise à jour
    qDebug() << "Statistiques mises à jour et graphique actualisé.";
}





void MainWindow::on_rechercher_idrf_clicked()
{
    // Récupérer l'ID RFID depuis le QLineEdit
    QString rfidID = ui->lineEdit_idrf->text().trimmed();

    // Requête SQL pour rechercher le fournisseur par RFID
    QSqlQuery query;
    query.prepare("SELECT ID, NOM FROM NAWRES.FOURNISSEURS WHERE RFID_ID = :rfid");
    query.bindValue(":rfid", rfidID);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Impossible d'exécuter la requête !");
        return;
    }

    static bool dataSent = false; // Variable statique pour vérifier si les données ont déjà été envoyées

    if (query.next() && !dataSent) { // Vérifier que les données ne sont pas envoyées deux fois
        // Récupérer les données
        int idFournisseur = query.value("ID").toInt();
        QString nomFournisseur = query.value("NOM").toString();

        // Mettre à jour le QLineEdit et QLabel avec les valeurs récupérées
        ui->lineEdit_FournisseurNom->setText(nomFournisseur);  // Afficher le nom dans le QLineEdit
        ui->label_id->setText(QString::number(idFournisseur));  // Afficher l'ID dans le QLabel

        // Construire la chaîne de données à envoyer à l'Arduino
        QString dataToSend = QString("ID:%1;Nom:%2")
                                 .arg(idFournisseur)
                                 .arg(nomFournisseur);
        arduino.write_to_arduino(dataToSend.toUtf8());
        // Envoyer les données à l'Arduino
        qDebug() << "Données envoyées à Arduino :" << dataToSend;

        dataSent = true; // Marquer comme envoyé
        QTimer::singleShot(1000, [&]() { dataSent = false; }); // Réinitialiser après 1 seconde

        // Ajouter un délai de 3 secondes avant de revenir à l'état initial
        QTimer::singleShot(5000, [&]() {
            ui->lineEdit_FournisseurNom->clear();  // Effacer le nom du fournisseur
            ui->label_id->clear();  // Effacer l'ID du fournisseur
            ui->lineEdit_idrf->clear();  // Effacer le champ RFID

            // Réinitialiser l'affichage avec un message d'attente
            ui->lineEdit_FournisseurNom->setText("Attente info...");
            ui->label_id->setText("ID...");
        });

    } else if (!dataSent) {
        qDebug() << "Fournisseur non trouvé pour l'ID RFID:" << rfidID;
        QMessageBox::information(this, "Fournisseur introuvable", "Aucun fournisseur trouvé avec cet ID RFID.");

        // Envoyer un message d'erreur à l'Arduino
        QString errorMessage = "Erreur:Fournisseur non trouve";
        arduino.write_to_arduino(errorMessage.toUtf8());
        qDebug() << "Message d'erreur envoyé à Arduino :" << errorMessage;
    }
}
void MainWindow::readSerialData() {
    if (arduino.getserial()->isReadable()) {
        QByteArray receivedData = arduino.read_from_arduino();  // Lire les données brutes

        qDebug() << "Données reçues (brutes) :" << receivedData;  // Afficher les données brutes reçues

        // Accumuler l'ID RFID en évitant les caractères de retour à la ligne (\r, \n)
        rfidID += QString(receivedData).replace("\r", "").replace("\n", "");  // Supprimer les retours chariot et sauts de ligne

        qDebug() << "ID RFID accumulé :" << rfidID;  // Afficher l'ID accumulé dans les logs

        // Vérifier si l'ID complet est reçu (longueur 6 ou 8 caractères)
        if (rfidID.length() == 6 || rfidID.length() == 8) {
            // Vérifier si l'ID RFID est valide (format hexadécimal)
            bool isValid = true;
            for (int i = 0; i < rfidID.length(); ++i) {
                QChar c = rfidID[i];
                if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                // Recherche du fournisseur en fonction de l'ID RFID
                QSqlQuery query;
                query.prepare("SELECT NOM FROM FOURNISSEURS WHERE RFID_ID = :rfid_id");
                query.bindValue(":rfid_id", rfidID);

                if (query.exec()) {
                    if (query.next()) {
                        QString nom = query.value(0).toString();  // Récupérer le nom du fournisseur
                        qDebug() << "Nom du fournisseur trouvé :" << nom;

                        // Mettre à jour le QLabel avec le nom du fournisseur
                        ui->label_nom->setText(nom);  // Afficher le nom dans le QLabel

                        // Mettre à jour le QLineEdit avec l'ID RFID
                        ui->lineEdit_FournisseurID->setText(rfidID);  // Afficher l'ID RFID dans le QLineEdit

                        // Envoyer le nom du fournisseur à l'écran LCD
                        sendNameToLCD(nom);
                    } else {
                        qDebug() << "Aucun fournisseur trouvé pour le RFID_ID :" << rfidID;

                        // Si aucun fournisseur n'est trouvé, afficher un message d'erreur
                        ui->label_nom->setText("Fournisseur non trouvé");
                        ui->lineEdit_FournisseurID->setText(rfidID);
                    }
                } else {
                    qDebug() << "Erreur SQL :" << query.lastError().text();
                }
            } else {
                qDebug() << "ID RFID invalide :" << rfidID;
            }

            // Réinitialiser l'ID RFID après la recherche
            rfidID.clear();
        } else if (rfidID.length() > 8) {
            // Réinitialiser si l'accumulation dépasse 8 caractères
            qDebug() << "ID RFID trop long, réinitialisation :" << rfidID;
            rfidID.clear();
        }
    } else {
        qDebug() << "Le port série n'est pas lisible.";
    }
}

// Fonction pour envoyer le nom à l'écran LCD via la communication série
void MainWindow::sendNameToLCD(const QString &nom) {
    // Assurez-vous que l'écran LCD est correctement initialisé
    // Envoyer le nom du fournisseur à l'écran LCD (via Arduino ou autre méthode série)
    qDebug() << "Envoi du nom du fournisseur à l'écran LCD : " << nom;

    // Si vous utilisez Arduino pour contrôler l'écran LCD, vous pouvez envoyer une commande série
    // Exemple pour Arduino : envoyer le nom à l'écran LCD via communication série
    arduino.write(nom.toUtf8());  // Convertir le nom en UTF-8 et l'envoyer à Arduino

    // Vous pouvez envoyer un caractère spécial pour indiquer la fin de l'affichage (optionnel)
    arduino.write("\n");  // Exemple : envoyer un saut de ligne pour marquer la fin de l'affichage
}
