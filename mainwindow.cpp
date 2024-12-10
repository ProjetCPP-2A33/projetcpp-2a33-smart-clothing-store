#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "product.h"
#include "historique.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHeaderView>

#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTextStream>
#include <QPdfWriter>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QChartView>


QSerialPort serial;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   setupSerial();  // Initialisation de la communication série
   ui->tabWidget->setStyleSheet("QWidget {"
                                  "border-radius: 10px;"
                                  "border: 2px solid #4CAF50;"
                                  "background-color: #f0f0f0;"
                                  "}"
                                  "QWidget::item:hover {"
                                  "background-color: #e1f5e1;"
                                  "border-radius: 5px;"
                                  "}"
                                "QTabBar::tab:hover {"
                                    "    background-color: #e1f5e1;"      /* Fond au survol (vert clair) */
                                    "    border-color: #388E3C;"           /* Bordure plus foncée au survol */
                                    "}"
                                    "QTabBar::tab:selected {"
                                    "    background-color: #4CAF50;"       /* Fond vert pour l'onglet sélectionné */
                                    "    color: white;"                    /* Texte blanc pour l'onglet sélectionné */
                                    "    border-color: #388E3C;}");

   QStackedWidget* stackedWidget = ui->stackedWidget;
       QWidget* page = stackedWidget->widget(0);
       QTableView* tableView = page->findChild<QTableView*>("tableView");
    // create and establish a connection
       if(tableView){
    Connection c;
    product prod;
    if (c.createconnect()) {
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);

        tableView->setModel(prod.afficher());
                    tableView->resizeColumnsToContents();
                    tableView->horizontalHeader()->setStretchLastSection(true);
                    displayCharts_clientByGender();

    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                              QObject::tr("Connection failed.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
       }



       /////////////////ARDUINOOO////////////////////
                    //TAKE THIS
                    arduino = new QSerialPort(this);
                    arduino->setPortName("COM4"); // Replace with your actual serial port name
                    arduino->open(QIODevice::ReadWrite); // Open for read and write
                    arduino->setBaudRate(QSerialPort::Baud9600);
                    arduino->setDataBits(QSerialPort::Data8);
                    arduino->setParity(QSerialPort::NoParity);
                    arduino->setStopBits(QSerialPort::OneStop);
                    arduino->setFlowControl(QSerialPort::NoFlowControl);


                    connect(arduino, &QSerialPort::readyRead, this ,&MainWindow::readData);
                   // readFromArduino22();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readData() {
    QByteArray data = arduino->readAll();  // Read the incoming data
    qDebug() << "Received Data: " << data; // Print the received data to the console

    // Optionally, you can update the UI (e.g., a QLabel) to display the message
    ui->label->setText(data);  // Assuming you have a QLabel named label
}

void MainWindow::readFromArduino22()
{
    QByteArray data = arduino->readAll();
    if (data.contains("START_RUN")) {
        qDebug() << "Received START_RUN from Arduino";
       // startrun();
    }
}

void MainWindow::on_pushButton_ajouter_clicked()
{  //lzm ikoun dispo/nondispo 8 caractere max 5tr
    // Récupération des informations saisies dans les champs de texte
    int id = ui->lineEdit_id->text().toInt();  // ID du produit (assurez-vous d'utiliser le bon champ)
    QString nom = ui->lineEdit_nom->text();    // Nom du produit
    QString taille = ui->lineEdit_taille->text();  // Taille du produit
    QString genre = ui->lineEdit_genre->text();  // Genre du produit
    int prix = ui->lineEdit_prix->text().toInt();  // Prix du produit
    QString statut = ui->lineEdit_statut->text();  // Récupère le statut sélectionné

    // Création d'une instance de la classe product avec les informations récupérées
    product nouveauProduit(nom, taille, genre, statut, id, prix);  // Statut défini ici comme "Disponible"

    // Appel de la méthode ajouter pour insérer le produit dans la base de données
    if (nouveauProduit.ajouter()) {
        //actualiser
        ui->tableView->setModel(nouveauProduit.afficher());
        QMessageBox::information(this, "Succès", "Produit ajouté avec succès!");
        // Add history
        historique histo;
        histo.setDATE_ACTION(QDateTime::currentDateTime());
        histo.setTYPE_ACTION("Ajout");
        histo.setDETAILS("Un produit est ajoute: " + nom );
        histo.Ajouterhistorique();

        // Save history to file

        QFile file("C:/Users/miriam/Desktop/projet QT/connexionBD/historique.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Impossible d'ouvrir le fichier!";
        }

        QTextStream out(&file);
        out << "Date: " << histo.getDATE_ACTION().toString() << ", Type: " << histo.getTYPE_ACTION() << ", Details: " << histo.getDETAILS() << "\n";

        file.close();
        qDebug() << "Historique est enregistré avec succes!";

    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du produit.");
    }
}

void MainWindow::on_pushButton_rechparid_clicked()
{
    // Récupérer l'ID du produit à rechercher
    int id = ui->lineEdit_id_recherche->text().toInt();  // Assurez-vous que le champ est bien un ID valide

    // Création de l'objet produit
    product produit;

    // Effectuer la recherche dans la base de données
    QSqlQueryModel* model = produit.rechercherparid(id);

    // Si le modèle a des données (c'est-à-dire qu'un produit a été trouvé)
    if (model->rowCount() > 0) {
        // Afficher le résultat dans la table
        ui->tableView->setModel(model);
    } else {
        // Si aucun produit n'est trouvé, afficher un message d'erreur
        QMessageBox::warning(this, "Produit introuvable", "Aucun produit trouvé avec cet ID.");
    }
}


void MainWindow::on_pushButton_recheparnom_clicked()
{
    // Récupérer le nom du produit à rechercher
    QString nom = ui->lineEdit_recherche_nom->text().trimmed();  // Assurez-vous que l'utilisateur saisit un nom valide

    // Création de l'objet produit
    product produit;

    // Effectuer la recherche dans la base de données
    QSqlQueryModel* model = produit.rechercherparnom(nom);

    // Si le modèle a des données (c'est-à-dire qu'un produit a été trouvé)
    if (model->rowCount() > 0) {
        // Afficher le résultat dans la table
        ui->tableView->setModel(model);
    } else {
        // Si aucun produit n'est trouvé, afficher un message d'erreur
        QMessageBox::warning(this, "Produit introuvable", "Aucun produit trouvé avec ce nom.");
    }
}

void MainWindow::on_pushButton_modifier_clicked() {
    // Récupération des informations saisies dans les champs de texte
    int id = ui->lineEdit_id_modif->text().toInt();
    QString nom = ui->lineEdit_nom_modif->text();
    QString taille = ui->lineEdit_taille_modif->text();
    QString genre = ui->lineEdit_genre_modif->text();
    int prix = ui->lineEdit_prix_modif->text().toInt();
    QString statut = ui->lineEdit_statut_modif->text();

    // Création d'une instance de la classe product avec les nouvelles informations
    product produitModifie(nom, taille, genre, statut, id, prix);

    // Appel de la méthode modifier pour mettre à jour le produit dans la base de données
    if (produitModifie.modifier()) {
        // Actualiser la tableView pour afficher les produits mis à jour
        ui->tableView->setModel(produitModifie.afficher());
        // Effacer le contenu des widgets
        ui->lineEdit_id_modif->clear();
        ui->lineEdit_nom_modif->clear();
        ui->lineEdit_taille_modif->clear();
        ui->lineEdit_genre_modif->clear();
        ui->lineEdit_prix_modif->clear();
        ui->lineEdit_statut_modif->clear();




        QMessageBox::information(this, "Succès", "Produit modifié avec succès !");

        // Add history
        historique histo;
        histo.setDATE_ACTION(QDateTime::currentDateTime());
        histo.setTYPE_ACTION("Modification");
        histo.setDETAILS("Un produit a été modifie: " + nom );
        histo.Ajouterhistorique();

        // Save history to file
        QFile file("C:/Users/miriam/Desktop/projet QT/connexionBD/historique.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Impossible d'ouvrir le fichier!";
        }

        QTextStream out(&file);
        out << "Date: " << histo.getDATE_ACTION().toString() << ", Type: " << histo.getTYPE_ACTION() << ", Details: " << histo.getDETAILS() << "\n";

        file.close();
        qDebug() << "Historique est enregistré avec succes!";




    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du produit. Vérifiez les informations saisies.");
    }
}


void MainWindow::on_pushButton_trier_clicked()
{
    // Récupérer la valeur du QLineEdit où l'utilisateur saisit le choix
    QString choix = ui->lineEdit_trier->text().trimmed();  // Récupère le texte du QLineEdit, trimé pour enlever les espaces inutiles

    bool croissant = false;  // Par défaut, le tri est décroissant

    // Vérifier la valeur du QLineEdit et ajuster la variable croissant
    if (choix.toLower() == "croissant") {
        croissant = true;
    } else if (choix.toLower() == "decroissant") {
        croissant = false;
    } else {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer 'croissant' ou 'decroissant'.");
        return;
    }

    // Appeler la fonction triparprix en fonction du choix
    product produit;
    QSqlQueryModel* model = produit.triparprix(croissant);

    // Mettre à jour le modèle dans la tableView
    ui->tableView->setModel(model);
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_id_supp->text().toInt();
    QString nom;

    // Retrieve the product name BEFORE deletion
    QSqlQuery query;
    query.prepare("SELECT NOM_PROD FROM PRODUIT WHERE ID_PROD = :id");
    query.bindValue(":id", id);
    // Execute the query and suppress the error output if it fails
    if (!query.exec()) {
        // Comment out or remove the error handling line that prints the error
        // qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    if (query.next()) {
         nom = query.value(0).toString();
        qDebug() << "Product found:" << nom;
    } else {
        qDebug() << "No product found with id:" << id;
    }

    // Proceed with the deletion
    product nouveauProduit;
    if (nouveauProduit.supprimer(id)) {
        // Refresh (actualize)
        ui->tableView->setModel(nouveauProduit.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);

        // Add history
        historique histo;
        histo.setDATE_ACTION(QDateTime::currentDateTime());
        histo.setTYPE_ACTION("Suppression");
        histo.setDETAILS("Supprimer produit avec le nom : " + nom);
        histo.Ajouterhistorique();

        // Save history to file
        QFile file("C:/Users/miriam/Desktop/projet QT/connexionBD/historique.txt");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            qDebug() << "Impossible d'ouvrir le fichier!";

        }

        QTextStream out(&file);
        out << "Date: " << histo.getDATE_ACTION().toString() << ", Type: " << histo.getTYPE_ACTION()
            << ", Details: " << histo.getDETAILS() << "\n";

        file.close();
        qDebug() << "Historique enregistré avec succès!";
    } else {
        // Deletion failed
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }
}

void MainWindow::displayCharts_clientByGender()
{
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->setBackgroundBrush(QBrush(QColor(173, 216, 230, 51))); // 51 is the alpha value (20% opacity)

    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

    QSqlQuery query;
    query.exec("SELECT GENRE_PROD, COUNT(*) FROM PRODUIT GROUP BY GENRE_PROD");

    int totalProduit = 0;

    while (query.next()) {
        QString gender = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(gender + ": " + QString::number(count), count);
        totalProduit += count;
    }

    chart->addSeries(series);
    chart->setTitle(QString("<div style='text-align: center;'><font size='4'>Total number of products = %1</font></div><div style='text-align: center;'><font size='4'>products by Gender</font></div>").arg(totalProduit));

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(700, 550);

    QPixmap pixmap = chartView->grab();
    ui->stat_label->setPixmap(pixmap);
}

void MainWindow::on_pushButton_statistique_clicked()
{
    displayCharts_clientByGender();
    ui->stackedWidget->setCurrentIndex(2);
}




void MainWindow::on_pushButton_exporterpdf_clicked()
{
    // Choix du fichier pour enregistrer le PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer sous", "", "PDF Files (*.pdf);;All Files (*)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Annulation", "Aucun fichier sélectionné !");
        return;
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter(&printer);
    int yPosition = 100;  // Position initiale sur l'axe Y

    // Titre
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(100, yPosition, "Liste des Produits");
    yPosition += 50;

    // Accéder au modèle de la table
    QAbstractItemModel *model = ui->tableView->model();
    if (!model) {
        QMessageBox::warning(this, "Erreur", "Aucune donnée à exporter !");
        return;
    }

    // Configuration de la police pour les données
    painter.setFont(QFont("Arial", 10));

    // Itérer sur les lignes et colonnes du modèle
    for (int row = 0; row < model->rowCount(); ++row) {
        QString rowData;
        for (int col = 0; col < model->columnCount(); ++col) {
            rowData += model->data(model->index(row, col)).toString() + " | ";
        }

        // Écrire chaque ligne dans le PDF
        painter.drawText(100, yPosition, rowData);
        yPosition += 25;

        // Vérifier si une nouvelle page est nécessaire
        if (yPosition > printer.pageRect().height() - 100) {
            printer.newPage();
            yPosition = 100;
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Données exportées en PDF avec succès !");
}
void MainWindow::on_pushButton_recommenknn_clicked()
{  // Créer une instance de la classe 'product' pour appeler la fonction non statique
    product p;
    // Valeur k pour la recommandation KNN
    int k = 5;  // Par exemple, recommander les 5 produits les plus proches

    // Appel de la fonction de recommandation KNN
    QVector<int> recommendedProductIds = p.recommendationparknn(k);

    // Préparer les données pour l'affichage dans la table (QTableView)
    QSqlQuery query;
    QStringList headers;
    headers << "ID" << "Nom" << "Taille" << "Genre" << "Statut" << "Prix";

    // Créer un modèle pour afficher les données dans QTableView
    QStandardItemModel *model = new QStandardItemModel(recommendedProductIds.size(), 6, this);
    model->setHorizontalHeaderLabels(headers);

    // Remplir le modèle avec les produits recommandés
    for (int i = 0; i < recommendedProductIds.size(); ++i) {
        query.prepare("SELECT ID_PROD, NOM_PROD, TAILLE_PROD, GENRE_PROD, STATUT_PROD, PRIX_PROD FROM PRODUIT WHERE ID_PROD = :idProd");
        query.bindValue(":idProd", recommendedProductIds[i]);
        query.exec();

        if (query.next()) {
            model->setItem(i, 0, new QStandardItem(query.value(0).toString()));  // ID
            model->setItem(i, 1, new QStandardItem(query.value(1).toString()));  // Nom
            model->setItem(i, 2, new QStandardItem(query.value(2).toString()));  // Taille
            model->setItem(i, 3, new QStandardItem(query.value(3).toString()));  // Genre
            model->setItem(i, 4, new QStandardItem(query.value(4).toString()));  // Statut
            model->setItem(i, 5, new QStandardItem(query.value(5).toString()));  // Prix
        }
    }

    // Afficher les données dans une QTableView
    ui->tableView_recommendations->setModel(model);
}




void MainWindow::on_tableView_recommendations_clicked(const QModelIndex &index)
{ // Lorsque l'utilisateur clique sur une ligne dans la table
    int row = index.row();

    // Récupérer les informations du produit sélectionné
    QString nom = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();  // Nom
    QString taille = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();  // Taille
    QString genre = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString();  // Genre
    int prix = ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toInt();  // Prix
    QString statut = ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString();  // Statut
    int id = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();  // ID

    // Remplir les champs de texte avec ces informations
    ui->lineEdit_id_modif->setText(QString::number(id));  // Remplir l'ID
    ui->lineEdit_nom_modif->setText(nom);  // Remplir le nom
    ui->lineEdit_taille_modif->setText(taille);  // Remplir la taille
    ui->lineEdit_genre_modif->setText(genre);  // Remplir le genre
    ui->lineEdit_prix_modif->setText(QString::number(prix));  // Remplir le prix
    ui->lineEdit_statut_modif->setText(statut);  // Remplir le statut

}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();

    // Récupérer les informations du produit sélectionné
    QString nom = ui->tableView->model()->data(ui->tableView->model()->index(row, 1)).toString();  // Nom
    QString taille = ui->tableView->model()->data(ui->tableView->model()->index(row, 2)).toString();  // Taille
    QString genre = ui->tableView->model()->data(ui->tableView->model()->index(row, 3)).toString();  // Genre
    int prix = ui->tableView->model()->data(ui->tableView->model()->index(row, 4)).toInt();  // Prix
    QString statut = ui->tableView->model()->data(ui->tableView->model()->index(row, 5)).toString();  // Statut
    int id = ui->tableView->model()->data(ui->tableView->model()->index(row, 0)).toInt();  // ID

    // Remplir les champs de texte avec ces informations
    ui->lineEdit_id_modif->setText(QString::number(id));  // Remplir l'ID
    ui->lineEdit_nom_modif->setText(nom);  // Remplir le nom
    ui->lineEdit_taille_modif->setText(taille);  // Remplir la taille
    ui->lineEdit_genre_modif->setText(genre);  // Remplir le genre
    ui->lineEdit_prix_modif->setText(QString::number(prix));  // Remplir le prix
    ui->lineEdit_statut_modif->setText(statut);  // Remplir le statut
}

void MainWindow::on_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
//fonction setupSerial
void MainWindow::setupSerial() {
    /*
    serial.setPortName("COM4");  // Remplacez par le port série approprié
    serial.setBaudRate(QSerialPort::Baud9600);
    if (serial.open(QIODevice::ReadWrite)) {
        connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readSerial);
    } else {
        qDebug() << "Erreur : Impossible d'ouvrir le port série.";
    }
    */
}

//lire les données arduino
void MainWindow::readSerial() {
    /*
    QByteArray data = serial.readAll();
    QString message = QString::fromUtf8(data).trimmed();

    if (message == "Check Availability") {
        int unavailableCount = checkUnavailableProducts();

        // Envoie les données à l'Arduino
        QString response = (unavailableCount > 0) ?
            QString("Unavailable: %1").arg(unavailableCount) : "All Available";

        serial.write(response.toUtf8());

        // Affiche un message dans l'interface Qt
        QMessageBox::information(this, "Produits indisponibles",
            unavailableCount > 0
            ? QString("Nombre de produits indisponibles : %1").arg(unavailableCount)
            : "Tous les produits sont disponibles.");
    }
    */
}



//elle interroge la base de données pour trouver les produits indispo
//int MainWindow::checkUnavailableProducts() {
    /*
    int count = 0;
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PRODUIT WHERE STATUT_PROD = 'non dispo'");
    if (query.exec() && query.next()) {
        count = query.value(0).toInt();
    }
    return count;
    */





