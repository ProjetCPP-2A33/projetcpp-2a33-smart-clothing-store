#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "employe.h"
#include <QSqlQuery>
#include <QPixmap>
#include <QPalette>
#include <QLabel>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QMessageBox>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QNetworkAccessManager>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPieSlice>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include "arduino.h"
#include "commande.h"
#include "fournisseur.h"
#include <QRegularExpression>
//include for the sms fonction
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QTextStream>


#include <QSerialPortInfo>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>

#include "client.h"


#include <QDebug>
#include <QSqlQueryModel>


#include <QPageSize>
#include <QPageLayout>
#include <QTableView>
#include <QHeaderView>
#include <QGraphicsEllipseItem>  // Ajoutez cette ligne
#include <QGraphicsScene>
#include <QVBoxLayout>
#include "ImageDelegate.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QStandardItemModel>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QPixmap>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QSqlRecord>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsScene>
#include <QThread>
#include "fournisseur.h"
#include <QSerialPort>
#include "equipment.h"
QSerialPort arduino;

Commande commande;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    employe e;
   arduino = new Arduino();
    ui->emptable_2->setModel(e.afficherEmploye());
    ui->emptable_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->stackedWidgetprincipale->setCurrentWidget(ui->pageconnection);
    /////commande///////////////
    highlightOrderDates();
    // connect(ui->rechercher_idrf, &QPushButton::clicked, this, &MainWindow::on_rechercher_idrf_clicked);
    connect(ui->calendarWidget_cd, &QCalendarWidget::selectionChanged, this, &MainWindow::on_calendarWidget_cd_selectionChanged);
    ui->tableView_commande->setModel(commande.afficher());
    populateStatutComboBox();
    displayCommandeStat();
    populateClientComboBox();
     connect(arduino->getserial(), &QSerialPort::readyRead, this, &MainWindow::readSerialData);
    QPushButton *lightButton = new QPushButton("Light Mode");
    QPushButton *nightButton = new QPushButton("Night Mode");
    connect(ui->modification_fournissurs, SIGNAL(clicked()), this, SLOT(on_modification_fournissurs_clicked()));
     connect(arduino->getserial(), &QSerialPort::readyRead, this, &MainWindow::readSerialData);
  // connect(arduino->getserial(), &QSerialPort::readyRead, this, &MainWindow::readSerialData);
     connect(serial, &QSerialPort::readyRead, this, &MainWindow::readFromArduino);
    QVBoxLayout *layout = new QVBoxLayout(this);  // Use 'this' to apply layout to this widget

    // Add buttons to the layout
    layout->addWidget(lightButton);
    layout->addWidget(nightButton);

    // Set the layout to the central widget (this is usually your main widget)
    setLayout(layout);

    // Connect the buttons to their respective slots

    connect(ui->calculerDurabilite, &QPushButton::clicked, this, &MainWindow::on_calculerDurabilite_clicked);
    connect(ui->trierButton, &QPushButton::clicked, this, &MainWindow::on_trierParNom_clicked);
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(int)), this, SLOT(updateIdField()));
    connect(ui->rechercheLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_recherche_textChanged);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::exporterPDF);

    connect(ui->notification_sms, &QPushButton::clicked, this, &MainWindow::on_notification_sms_clicked); // Connexion du bouton
    ui->id->setValidator(new QIntValidator(0, 999999, this)); // ID validator
    ui->age->setValidator(new QIntValidator(0, 50, this));  // Age validator (assuming age <= 50)
    ui->numtel->setValidator(new QIntValidator(100000000, 999999999, this)); // Phone number validator (9 digits)
    ui->age_2->setValidator(new QIntValidator(0, 50, this));  // Age validator (assuming age <= 50)
    ui->numtel_2->setValidator(new QIntValidator(100000000, 999999999, this)); // Phone number validator (9 digits)

      ui->tableView->setModel(Etmp.afficher()); // Afficher les fournisseur dans le tableau
    connect(arduino->getserial(), &QSerialPort::readyRead, this, &MainWindow::readSerialData);

    // Utilisation de QRegularExpressionValidator pour valider les champs texte
    ui->nom->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-zàâçéèêëîïôûùüÿ]+( [A-Za-zàâçéèêëîïôûùüÿ]+)*"), this));  // Nom
    ui->prenom->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-zàâçéèêëîïôûùüÿ]+( [A-Za-zàâçéèêëîïôûùüÿ]+)*"), this));  // Prénom
    ui->nom_2->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-zàâçéèêëîïôûùüÿ]+( [A-Za-zàâçéèêëîïôûùüÿ]+)*"), this));  // Nom
    ui->prenom_2->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-zàâçéèêëîïôûùüÿ]+( [A-Za-zàâçéèêëîïôûùüÿ]+)*"), this));  // Prénom

    COMPORT = new QSerialPort();
    COMPORT->setPortName("COM5");
    COMPORT->setBaudRate(QSerialPort::BaudRate::Baud9600);
    COMPORT->setParity(QSerialPort::Parity::NoParity);
    COMPORT->setDataBits(QSerialPort::DataBits::Data8);
    COMPORT->setStopBits(QSerialPort::StopBits::OneStop);
    COMPORT->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    COMPORT->open(QIODevice::ReadWrite);





    if (COMPORT->isOpen())
    {
        qDebug() << "Serial Port Is Connected.";
        qDebug() << COMPORT->error();
    }
    else
    {
        qDebug() << "Serial Port Is Not Connected.";
        qDebug() << COMPORT->error();
    }

    connect(COMPORT,SIGNAL(readyRead()),this,SLOT(Read_Data()));


    setupArduino();     // Con


    ////////////////////////////////////////////////
    connect(ui->updateFindBtn, &QPushButton::clicked, this, &MainWindow::findEquipmentToUpdate);
    connect(ui->deleteBtn, &QPushButton::clicked, this, &MainWindow::handleDeleteBtnClick);
     connect(ui->updateBtn, &QPushButton::clicked, this, &MainWindow::updateEquipment);
      connect(ui->searchBtn, &QPushButton::clicked, this, &MainWindow::handleSearchBtnClick);
        connect(ui->searchByNameBtn, &QPushButton::clicked, this, &MainWindow::handleSearchByNameBtnClick);
            connect(ui->ascBtn, &QPushButton::clicked, this, &MainWindow::sortEquipmentsAsc);
     connect(ui->descBtn, &QPushButton::clicked, this, &MainWindow::sortEquipmentsDesc);
      connect(ui->exportBtn, &QPushButton::clicked, this, &MainWindow::exportEquipmentsAsCSV);
     connect(ui->retrievePageBtn, &QPushButton::clicked, this, &MainWindow::goToRetrievePage);
     connect(ui->updatePageBtn, &QPushButton::clicked, this, &MainWindow::goToUpdatePage);
     connect(ui->deletePageBtn, &QPushButton::clicked, this, &MainWindow::goToDeletePage);
     connect(ui->addPageBtn, &QPushButton::clicked, this, &MainWindow::goToAddPage);
     connect(ui->searchPageBtn, &QPushButton::clicked, this, &MainWindow::goToSearchPage);
     connect(ui->sortPageBtn, &QPushButton::clicked, this, &MainWindow::goToSortPage);
     connect(ui->exportPageBtn, &QPushButton::clicked, this, &MainWindow::goToExportPage);
     connect(ui->searchByNamePageBtn, &QPushButton::clicked, this, &MainWindow::goToSearchByNamePage);
     connect(ui->statPageBtn, &QPushButton::clicked, this, &MainWindow::goToStatPage);

}


void MainWindow::setLightMode() {
    // Define the light mode color with 30% opacity for the background
    QString lightStyle = "QWidget { "
                         "background-color: rgba(246, 242, 197, 0.1); "  // Light background with 30% opacity
                         "color: rgb(255, 255, 255); "  // Black text color
                         "}";
    setStyleSheet(lightStyle);
}

void MainWindow::setNightMode() {
    // Define the night mode color with 30% opacity for the background
    QString nightStyle = "QWidget { "
                         "background-color: rgba(255, 255, 255, 0.1); "  // Dark background with 30% opacity
                         "color: rgb(246, 242, 197); "  // Light text color
                         "}";
    setStyleSheet(nightStyle);
}









void MainWindow::Read_Data()
{
    if (COMPORT->isOpen())

    {
        while (COMPORT->bytesAvailable())
        {
            Data_From_SerialPort += COMPORT->readAll();

            if (Data_From_SerialPort.endsWith('\n'))
            {
                IS_Data_Recevied = true;
            }
        }

        qDebug() << "Data From Serial Port:" << IS_Data_Recevied;

        if (IS_Data_Recevied)
        {
            QString datareceived = Data_From_SerialPort.trimmed();

            qDebug() << "Data From Serial Port:" << datareceived;
            ui->receiveddata->append(datareceived);

            QSqlQuery query;
            query.prepare("SELECT * FROM employe WHERE id_emp = :id_emp");
            query.bindValue(":id_emp", datareceived);
            QString responseMessage;

            if (query.exec())
            {
                if (query.next())
                {
                    qDebug() << "Valid ID : " << datareceived;
                    ui->receiveddata->append("Valid ID: " + datareceived + " Valid ID");
                    ui->receiveddata->setText(datareceived + "\n" + " Valid ID");

                    if (COMPORT->isWritable())
                    {
                        responseMessage = "Valid ID\n";
                        COMPORT->write(responseMessage.toUtf8());
                        qDebug() << "Response sent To Arduino: " << responseMessage;

                        QSqlQuery queryPassword;
                        queryPassword.prepare("SELECT mot_de_passe FROM employe WHERE id_emp = :id_emp");
                        queryPassword.bindValue(":id_emp", datareceived);

                        if (queryPassword.exec() && queryPassword.next())
                        {        ui->stackedWidgetprincipale->setCurrentWidget(ui->pagehomepage);

                            QString motDePasse = queryPassword.value(0).toString();
                            qDebug() << "Mot de passe for ID " << datareceived << ": " << motDePasse;

                            if (COMPORT->isWritable())
                            {
                                QString motDePasseMessage = motDePasse+"\n";
                                COMPORT->write(motDePasseMessage.toUtf8());
                                qDebug() << "Mot de passe sent to Arduino: " << motDePasseMessage;
                            }
                        }
                    }
                }
                else
                {
                    if (COMPORT->isWritable())
                    {
                        responseMessage = "ID invalid\n";
                        COMPORT->write(responseMessage.toUtf8());
                        qDebug() << "Response sent To Arduino: Invalid";
                    }

                    qDebug() << "Invalid ID. No match found for: " << datareceived;
                    ui->receiveddata->append("Invalid ID: " + datareceived);
                }
            }

            Data_From_SerialPort.clear();
            IS_Data_Recevied = false;
        }
    }
}





void MainWindow::onDataReceived() {
    Arduino arduino;

    QByteArray data = arduino.read_from_arduino();
    if (!data.isEmpty()) {
        qDebug() << "Data found:" << data;
        ui->receiveddata->append(data);
    } else {
        qDebug() << "No data received.";
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    QLabel *backgroundLabel = this->findChild<QLabel *>();
    if (backgroundLabel) {
        backgroundLabel->setGeometry(0, 0, this->width(), this->height());
        backgroundLabel->setPixmap(QPixmap(":/images/bg.jpeg").scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    }
}
void MainWindow::on_bouttonajouter_clicked()
{
    employe e;

    QString nom = ui->ajouternom_2->text();
    QString prenom = ui->ajouterprenom_2->text();
    QString mail = ui->ajoutermail_2->text();
    QString mot_de_passe = ui->ajoutermotdepasse_2->text();
    int num_tel = ui->ajouternumtel_2->text().toInt();
    QString adresse = ui->ajouteradresse_2->text();
    QString genre = ui->combogenre_3->currentText();

    e.setNom(nom);
    e.setPrenom(prenom);
    e.setMail(mail);
    e.setMotDePasse(mot_de_passe);
    e.setNumTel(num_tel);
    e.setAdresse(adresse);
    e.setGenre(genre);

    if (e.ajouterEmploye(e)) {
        QMessageBox::information(this, "Succès", "Employe ajouté avec succès!");
        ui->ajouternom_2->clear();
        ui->ajouterprenom_2->clear();
        ui->ajoutermail_2->clear();
        ui->ajoutermotdepasse_2->clear();
        ui->ajouternumtel_2->clear();
        ui->ajouteradresse_2->clear();
        ui->combogenre_3->setCurrentIndex(0);

        ui->emptable_2->setModel(e.afficherEmploye());
        historique("Ajout", "success", "Employe Ajouté " + nom);
        qDebug() << "Employe ajouté avec succès!";
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employe.");
        qDebug() << "Échec de l'ajout dans la base";
    }
}

void MainWindow::on_pushButton_clicked()
{

        ui->stackedWidgetemploye->setCurrentWidget(ui->pagestatistiques_2);

        // Vérifiez si un layout existe déjà pour éviter de le recréer à chaque fois
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui->pagestatistiques_2->layout());
        if (!layout) {
            layout = new QVBoxLayout(ui->pagestatistiques_2);
            ui->pagestatistiques_2->setLayout(layout);
        }

        // Supprimer les anciens widgets du layout pour éviter les doublons
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Création du graphique
        QPieSeries *series = new QPieSeries();

        QSqlQuery query;
        query.exec("SELECT COUNT(*) FROM employe WHERE nom = 'a'");
        int malecount = query.next() ? query.value(0).toInt() : 0;

        query.exec("SELECT COUNT(*) FROM employe WHERE nom = 'Jane'");
        int femalecount = query.next() ? query.value(0).toInt() : 0;

        int totalCount = malecount + femalecount;

        QPieSlice *maleSlice = series->append("male", malecount);
        QPieSlice *femaleSlice = series->append("female", femalecount);

        maleSlice->setExploded();
        maleSlice->setExplodeDistanceFactor(0.3);
        maleSlice->setLabelVisible();
        maleSlice->setBrush(QColor(0, 0, 255)); // Couleur bleue

        femaleSlice->setExploded();
        femaleSlice->setExplodeDistanceFactor(0.3);
        femaleSlice->setLabelVisible();
        femaleSlice->setBrush(QColor(255, 0, 0)); // Couleur rouge

        maleSlice->setLabel(QString("male: %1%").arg(static_cast<double>(malecount) / totalCount * 100, 0, 'f', 1));
        femaleSlice->setLabel(QString("female: %1%").arg(static_cast<double>(femalecount) / totalCount * 100, 0, 'f', 1));

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::AllAnimations);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Ajouter le graphique au layout existant
        layout->addWidget(chartView);



}

void MainWindow::on_button_supprimer_clicked()
{
    employe p;
    int id_emp = ui->idsupprimer_2->text().toInt();

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM employe WHERE id_emp = :id_emp");
    checkQuery.bindValue(":id_emp", id_emp);

    if (!checkQuery.exec() || !checkQuery.next() || checkQuery.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Employe introuvable", "Aucun employe trouvé avec cet ID.");
        return;
    }

    if (p.supprimerEmploye(id_emp)) {
        qDebug() << "Employe supprimé avec succès!";
        QMessageBox::information(this, "Succès", "Employe supprimé avec succès!");

        ui->idsupprimer_2->clear();
        ui->emptable_2->setModel(p.afficherEmploye());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidgetemploye->setCurrentWidget(ui->page_4);

    QString filePath = QCoreApplication::applicationDirPath() + "/historique.txt";
    QFile file(filePath);

   /* if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur","fichier historique vide");
        return;
    }*/

    QTextStream in(&file);
    QString historiqueContent = in.readAll();
    file.close();

    ui->textHistorique_2->setPlainText(historiqueContent);
}

void MainWindow::on_bouttonrecherchetableau_clicked()
{

}


void MainWindow::on_pushButton_3_clicked()
{
    employe e ;
    QSqlQueryModel *model = e.trieparnom();
    if(model){
        ui->emptable_2->setModel(model);

    }


}


void MainWindow::on_bouttonafficheremloyes_clicked()
{
    employe e;
    ui->stackedWidgetemploye->setCurrentWidget(ui->pageafficheremployes_2);
    ui->emptable_2->setModel(e.afficherEmploye());
}


void MainWindow::on_bouttonafficherpagesupprimer_clicked()
{
    ui->stackedWidgetemploye->setCurrentWidget(ui->pagesupprimer_2);
}


void MainWindow::on_bouttonafficherajoutemploye_clicked()
{
    ui->stackedWidgetemploye->setCurrentWidget(ui->pageajouteremploye_2);
}


void MainWindow::on_bouttonrecherche_clicked()
{

        employe e;
    QString recherche = ui->inputrecherche_2->text();

    QSqlQueryModel* model = e.rechercheparnom(recherche);

    if (model) {
        ui->emptable_2->setModel(model);
    } else {
        qDebug() << "pas de model";
    }
}


void MainWindow::on_buttontriparnom_clicked()
{
    employe e;
    QSqlQueryModel* model = e.trieparnom();
    ui->emptable_2->setModel(model);

}

void MainWindow::on_bouttonexportpdf_clicked()
{
    QString dateAct = QDate::currentDate().toString("dd/MM/yyyy");

    QString html = "<div align='right'>" + dateAct + "</div>"
                                                     "<h1 align='center'>Rapport des Employés</h1>"
                                                     "<table border='1' align='center' cellspacing='0' cellpadding='5'>"
                                                     "<thead>"
                                                     "<tr>"
                                                     "<th>ID</th>"
                                                     "<th>Nom</th>"
                                                     "<th>Prénom</th>"
                                                     "<th>Email</th>"
                                                     "<th>Téléphone</th>"
                                                     "<th>Adresse</th>"
                                                     "</tr>"
                                                     "</thead>"
                                                     "<tbody>";

    QSqlQuery query("SELECT id_emp, nom, prenom, mail, num_tel, adresse FROM employe");
    while (query.next()) {
        html += "<tr>"
                "<td>" + query.value(0).toString() + "</td>"
                                              "<td>" + query.value(1).toString() + "</td>"
                                              "<td>" + query.value(2).toString() + "</td>"
                                              "<td>" + query.value(3).toString() + "</td>"
                                              "<td>" + query.value(4).toString() + "</td>"
                                              "<td>" + query.value(5).toString() + "</td>"
                                              "</tr>";
    }

    html += "</tbody></table>";

    QTextDocument document;
    document.setHtml(html);

    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "Fichiers PDF (*.pdf);;Tous les fichiers (*)");

    if (!filePath.isEmpty()) {
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);
        printer.setPageMargins(QMarginsF(15, 15, 15, 15));
        printer.setPageSize(QPageSize::A4);

        document.print(&printer);

        QMessageBox::information(this, "Succès", "Rapport PDF généré avec succès!");
        historique("Export PDF", filePath, "PDF: " + filePath);

    } else {
        QMessageBox::warning(this, "Erreur", "Aucun fichier sélectionné.");
    }
}

void MainWindow::on_bouttonafficherpagemodifieremploye_clicked()
{
    ui->stackedWidgetemploye->setCurrentWidget(ui->pagemodifieremloye_2);

}


void MainWindow::on_bouttonconfirmermodif_clicked()
{
    employe e;
    int id_emp = ui->idemployemodif_2->text().toInt();
    QString nom = ui->ajouternom_4->text();
    QString prenom = ui->ajouterprenom_4->text();
    QString mail = ui->ajoutermail_4->text();
    QString mot_de_passe = ui->ajoutermotdepasse_4->text();
    int num_tel = ui->ajouternumtel_4->text().toInt();
    QString adresse = ui->ajouteradresse_4->text();
    QString genre = ui->combogenre_4->currentText(); // Get genre from combo box

    if (e.modifierEmploye(id_emp, nom, prenom, mail, mot_de_passe, num_tel, adresse, genre)) {
        qDebug() << "Employe modifié";
        QMessageBox::information(this, "Succès", "Employe modifié");
        historique("Modification", "success", "Employe Modifié " + QString::number(id_emp));

        ui->ajouternom_4->clear();
        ui->ajouterprenom_4->clear();
        ui->ajoutermail_4->clear();
        ui->ajoutermotdepasse_4->clear();
        ui->ajouternumtel_4->clear();
        ui->ajouteradresse_4->clear();
        ui->combogenre_4->setCurrentIndex(0); // Reset combo box to first item

        ui->emptable_2->setModel(e.afficherEmploye());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}

void MainWindow::on_bouttonconfirmeridmodif_clicked()
{

    int id_emp = ui->idemployemodif_2->text().toInt();

    // controle saisie sur l'id
    if (id_emp <= 0) {
        QMessageBox::warning(this, "ID invalide", "Veuillez introduire valid id");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT nom, prenom, mail, mot_de_passe, num_tel, adresse FROM employe WHERE id_emp = :id_emp");
    query.bindValue(":id_emp", id_emp);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur Base de Données", "echec requete ");
        qDebug() << "Query execution error:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString nom = query.value("nom").toString();
        QString prenom = query.value("prenom").toString();
        QString mail = query.value("mail").toString();
        QString mot_de_passe = query.value("mot_de_passe").toString();
        int num_tel = query.value("num_tel").toInt();
        QString adresse = query.value("adresse").toString();

        ui->ajouternom_4->setText(nom);
        ui->ajouterprenom_4->setText(prenom);
        ui->ajoutermail_4->setText(mail);
        ui->ajoutermotdepasse_4->setText(mot_de_passe);
        ui->ajouternumtel_4->setText(QString::number(num_tel));
        ui->ajouteradresse_4->setText(adresse);

    } else {
        QMessageBox::warning(this, "Employee introuvable", "ID employe introuvable");
    }
}


void MainWindow::historique(const QString &action, const QString &nomProduit, const QString &details) {
    QString filePath = QCoreApplication::applicationDirPath() + "/historique.txt";

    QFile file(filePath);

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Erreur", "fichier historique vide");
        return;
    }

    QTextStream out(&file);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    out << timestamp << " - Action: " << action << " - Produit: " << nomProduit << " - " << details << "\n";
    file.close();
}

void MainWindow::loadHistoriqueFile()
{
    QString filePath = QCoreApplication::applicationDirPath() + "/historique.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Erreur", "Fichier Historique vide");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    ui->textHistorique_2->setPlainText(content);
}



void MainWindow::on_bouttonformlogin_clicked()
{
    ui->stackedWidgetprincipale->setCurrentWidget(ui->pagehomepage);
}


void MainWindow::on_bouttonlogin_clicked()
{
    employe e ;
    QString username = ui->inputloginform_2->text();
    QString password = ui->inputloginmotdepasse_2->text();
        // controle de saisie sur login et le mot de passe
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "erreur input ", "username/password requis");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE nom = :nom AND mot_de_passe = :mot_de_passe");
    query.bindValue(":nom", username);
    query.bindValue(":mot_de_passe", password);

    if (!query.exec()) {
        QMessageBox::critical(this, "erreur requete", query.lastError().text());
        return;
    }

    if (query.next()) {
        QMessageBox::information(this, "LOGIN SUCCESS", "Welcome!");
        ui->stackedWidgetprincipale->setCurrentWidget(ui->pagehomepage);
        ui->inputloginform_2->clear();
        ui->inputloginmotdepasse_2->clear();

    } else {
        QMessageBox::warning(this, "Login ECHEC", "username ou password invalide");
    }


}


void MainWindow::on_bouttonaffichergestionemp_clicked()
{
    employe e ;

    ui->stackedWidgetprincipale->setCurrentWidget(ui->pageemp);
    ui->stackedWidgetemploye->setCurrentWidget(ui->pageafficheremployes_2);
    ui->emptable_2->setModel(e.afficherEmploye());
}


void MainWindow::on_bouttonconnection_clicked()
{
    employe e ;
    QString username = ui->inputloginform_2->text();
    QString password = ui->inputloginmotdepasse_2->text();
        // controle de saisie sur login et le mot de passe
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "erreur input ", "username/password requis");
        return;
    }
    qDebug() << "username " <<username;

    qDebug() << "password " <<password;

    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE nom = :nom AND mot_de_passe = :mot_de_passe");
    query.bindValue(":nom", username);
    query.bindValue(":mot_de_passe", password);

    if (!query.exec()) {
        QMessageBox::critical(this, "erreur requete", query.lastError().text());
        return;
    }

    if (query.next()) {
        QMessageBox::information(this, "LOGIN SUCCESS", "Welcome!");
       // ui->emptable_2->setModel(e.afficherEmploye());
        ui->stackedWidgetprincipale->setCurrentWidget(ui->pagehomepage);
        ui->inputloginform_2->clear();
        ui->inputloginmotdepasse_2->clear();

    } else {
        QMessageBox::warning(this, "Login ECHEC", "username ou password invalide");
    }

}


void MainWindow::on_bouttonafficheremloyes_2_clicked()
{
    employe e;
    ui->stackedWidgetemploye->setCurrentWidget(ui->pageafficheremployes_2);
    ui->emptable_2->setModel(e.afficherEmploye());
}


void MainWindow::on_bouttonafficherpagemodifieremploye_2_clicked()
{
    ui->stackedWidgetemploye->setCurrentWidget(ui->pagemodifieremloye_2);

}


void MainWindow::on_bouttonafficherajoutemploye_2_clicked()
{    ui->stackedWidgetemploye->setCurrentWidget(ui->pageajouteremploye_2);


}


void MainWindow::on_bouttonafficherpagesupprimer_2_clicked()
{
    ui->stackedWidgetemploye->setCurrentWidget(ui->pagesupprimer_2);
}


void MainWindow::on_bouttonajouter_2_clicked()
{
    employe e;

    QString nom = ui->ajouternom_2->text();
    QString prenom = ui->ajouterprenom_2->text();
    QString mail = ui->ajoutermail_2->text();
    QString mot_de_passe = ui->ajoutermotdepasse_2->text();
    int num_tel = ui->ajouternumtel_2->text().toInt();
    QString adresse = ui->ajouteradresse_2->text();
    QString genre = ui->combogenre_3->currentText();

    e.setNom(nom);
    e.setPrenom(prenom);
    e.setMail(mail);
    e.setMotDePasse(mot_de_passe);
    e.setNumTel(num_tel);
    e.setAdresse(adresse);
    e.setGenre(genre);

    if (e.ajouterEmploye(e)) {
        QMessageBox::information(this, "Succès", "Employe ajouté avec succès!");
        ui->ajouternom_2->clear();
        ui->ajouterprenom_2->clear();
        ui->ajoutermail_2->clear();
        ui->ajoutermotdepasse_2->clear();
        ui->ajouternumtel_2->clear();
        ui->ajouteradresse_2->clear();
        ui->combogenre_3->setCurrentIndex(0);

        ui->emptable_2->setModel(e.afficherEmploye());
        historique("Ajout", "success", "Employe Ajouté " + nom);
        qDebug() << "Employe ajouté avec succès!";
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employe.");
        qDebug() << "Échec de l'ajout dans la base";
    }
}


void MainWindow::on_bouttonconfirmeridmodif_2_clicked()
{

    int id_emp = ui->idemployemodif_2->text().toInt();

    // controle saisie sur l'id
    if (id_emp <= 0) {
        QMessageBox::warning(this, "ID invalide", "Veuillez introduire valid id");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT nom, prenom, mail, mot_de_passe, num_tel, adresse FROM employe WHERE id_emp = :id_emp");
    query.bindValue(":id_emp", id_emp);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur Base de Données", "echec requete ");
        qDebug() << "Query execution error:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString nom = query.value("nom").toString();
        QString prenom = query.value("prenom").toString();
        QString mail = query.value("mail").toString();
        QString mot_de_passe = query.value("mot_de_passe").toString();
        int num_tel = query.value("num_tel").toInt();
        QString adresse = query.value("adresse").toString();

        ui->ajouternom_4->setText(nom);
        ui->ajouterprenom_4->setText(prenom);
        ui->ajoutermail_4->setText(mail);
        ui->ajoutermotdepasse_4->setText(mot_de_passe);
        ui->ajouternumtel_4->setText(QString::number(num_tel));
        ui->ajouteradresse_4->setText(adresse);

    } else {
        QMessageBox::warning(this, "Employee introuvable", "id employe invalide");
    }
}


void MainWindow::on_button_supprimer_2_clicked()
{
    employe p;
    int id_emp = ui->idsupprimer_2->text().toInt();

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM employe WHERE id_emp = :id_emp");
    checkQuery.bindValue(":id_emp", id_emp);

    if (!checkQuery.exec() || !checkQuery.next() || checkQuery.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Employe introuvable", "Aucun employe trouvé avec cet ID.");
        return;
    }

    if (p.supprimerEmploye(id_emp)) {
        qDebug() << "Employe supprimé avec succès!";
        QMessageBox::information(this, "Succès", "Employe supprimé avec succès!");

        ui->idsupprimer_2->clear();
        ui->emptable_2->setModel(p.afficherEmploye());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression");
    }
}





void MainWindow::on_bouttonconfirmeidmodif_clicked()
{
    employe e;
    int id_emp = ui->idemployemodif_2->text().toInt();
    QString nom = ui->ajouternom_4->text();
    QString prenom = ui->ajouterprenom_4->text();
    QString mail = ui->ajoutermail_4->text();
    QString mot_de_passe = ui->ajoutermotdepasse_4->text();
    int num_tel = ui->ajouternumtel_4->text().toInt();
    QString adresse = ui->ajouteradresse_4->text();
    QString genre = ui->combogenre_4->currentText(); // Get genre from combo box

    if (e.modifierEmploye(id_emp, nom, prenom, mail, mot_de_passe, num_tel, adresse, genre)) {
        qDebug() << "Employe modifié";
        QMessageBox::information(this, "Succès", "Employe modifié");
        historique("Modification", "success", "Employe Modifié " + QString::number(id_emp));

        ui->ajouternom_4->clear();
        ui->ajouterprenom_4->clear();
        ui->ajoutermail_4->clear();
        ui->ajoutermotdepasse_4->clear();
        ui->ajouternumtel_4->clear();
        ui->ajouteradresse_4->clear();
        ui->combogenre_4->setCurrentIndex(0);

        ui->emptable_2->setModel(e.afficherEmploye());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}



void MainWindow::on_bouttonreaddata_clicked()
{
    Arduino arduino;
        QByteArray data = arduino.read_from_arduino();

        if (!data.isEmpty()) {
            qDebug() << "Data received:" << data;
            ui->receiveddata->append(data);
        } else {
            qDebug() << "No data received.";
        }


}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidgetprincipale->setCurrentIndex(3);
}

////////////////////////////////commande///////////////////////////

void MainWindow::populateStatutComboBox() {
    ui->comboBox_satut->addItem("Confrimee ");
    ui->comboBox_satut->addItem("Annulee");
    ui->comboBox_satut->addItem("En attente");
}



void MainWindow::on_ajouter_cd_clicked()
{

        // Récupérer les valeurs des champs de l'interface utilisateur
    QDate date_creation = ui->dateEdit_date->date();
    QString statut = ui->comboBox_satut->currentText();
    int quantity = ui->lineEdit_quantite->text().toInt();
    int montant_total = ui->lineEdit_montant->text().toInt();
    int id_client = ui->comboBox_client->currentData().toInt();
    /////////CONTROLE DE SAISIE
    // Check if the statut is selected
    if (statut.isEmpty()) {
        QMessageBox::warning(this, "Statut manquant", "Veuillez sélectionner un statut.");
        return;
    }

    // Check if the quantity and total amount are valid
    if (quantity <= 1) {
        QMessageBox::warning(this, "Quantité invalide", "La quantité doit être supérieure à 1.");
        return;
    }

    if (montant_total <= 1) {
        QMessageBox::warning(this, "Montant invalide", "Le montant total doit être supérieur à 1.");
        return;
    }


    // Check the validity of the date
    QDate aujourdhui = QDate::currentDate();
    if (!date_creation.isValid() || date_creation < aujourdhui) {
        QMessageBox::warning(this, "Date invalide", "La date de création doit être valide et ne peut pas être antérieure à aujourd'hui.");
        return;
    }

    // Créer une instance de la classe Commande avec les données récupérées
    Commande commande(date_creation, statut, quantity, montant_total, id_client);

    // Appeler la méthode ajouter() pour insérer les données dans la base de données
    bool success = commande.ajouter();

    // Afficher un message en fonction du résultat de l'opération
    if (success) {
        highlightOrderDates();
        sendOrderConfirmationSMS();
        displayCommandeStat();

        QMessageBox::information(this, "Succès", "La commande a été ajoutée avec succès.");

        // Optionnel : Effacer les champs après ajout
        ui->dateEdit_date->setDate(QDate::currentDate());
        ui->comboBox_satut->setCurrentIndex(-1);  // reset to no selection
        ui->lineEdit_montant->clear();
        ui->lineEdit_quantite->clear();

        // Optionnel : Mettre à jour l'affichage des commandes
        ui->tableView_commande->setModel(commande.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'ajout de la commande.");
    }
}





void MainWindow::on_modif_cd_clicked()
{
    // Retrieve values from the user interface
    int id = ui->idCommande->text().toInt();  // Assuming there's an ID field to identify the record
    QDate date_creation = ui->dateEdit_date->date();
    QString statut = ui->comboBox_satut->currentText();
    int quantite = ui->lineEdit_quantite->text().toInt();

    int montant_total = ui->lineEdit_montant->text().toInt();
    int id_client = ui->comboBox_client->currentData().toInt();

    // Create a Commande object with the updated data


    // Check if the ID is valid
    if (id <= 0) {
        QMessageBox::warning(this, "ID invalide", "Veuillez entrer un ID valide.");
        return;
    }

    // Check if the statut is selected
    if (statut.isEmpty()) {
        QMessageBox::warning(this, "Statut manquant", "Veuillez sélectionner un statut.");
        return;
    }

    // Check if the quantity and total amount are valid
    if (quantite <= 0) {
        QMessageBox::warning(this, "Quantité invalide", "La quantité doit être supérieure à zéro.");
        return;
    }

    if (montant_total <= 0) {
        QMessageBox::warning(this, "Montant invalide", "Le montant total doit être supérieur à zéro.");
        return;
    }

    // Check the validity of the date
    QDate aujourdhui = QDate::currentDate();
    if (!date_creation.isValid() || date_creation < aujourdhui) {
        QMessageBox::warning(this, "Date invalide", "La date de création doit être valide et ne peut pas être antérieure à aujourd'hui.");
        return;
    }
    Commande commande(id, date_creation, statut, quantite, montant_total, id_client);

    // Call the modifier() method to update the record in the database
    bool success = commande.modifier(id);

    // Display a message based on the result of the operation
    if (success) {
        highlightOrderDates();
        displayCommandeStat();
        QMessageBox::information(this, "Succès", "La commande a été modifiée avec succès.");

        // Optionally clear fields after modification
        ui->idCommande->clear();
        ui->dateEdit_date->setDate(QDate::currentDate());
        ui->comboBox_satut->setCurrentIndex(-1);  // Reset to no selection
        ui->lineEdit_quantite->clear();
        ui->lineEdit_montant->clear();

        // Optionally refresh the display
        ui->tableView_commande->setModel(commande.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la modification de la commande.");
    }
}


void MainWindow::on_supp_cd_clicked()
{
    // Get the selected index from the table view
    QModelIndex index = ui->tableView_commande->currentIndex();

    // Check if an index is selected
    if (!index.isValid()) {
        QMessageBox::warning(this, "Alerte", "Veuillez sélectionner une commande à supprimer.");
        return;
    }

    // Retrieve the ID of the selected command (assuming ID is in the first column)
    int id = ui->tableView_commande->model()->index(index.row(), 0).data().toInt();

    // Create a Commande object and call the supprimer method
    Commande commande;
    if (commande.supprimer(id)) {
        displayCommandeStat();
        QMessageBox::information(this, "Succès", "La commande a été supprimée avec succès.");

        // Refresh the table view to show updated data
        ui->tableView_commande->setModel(commande.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la suppression de la commande.");
    }
}


void MainWindow::on_pdf_cd_clicked()
{
  generatePDF("");
}


void MainWindow::on_tri_cd_clicked()
{
    QString champ = "date_creation";  // Default column in the database
    QString order = "ASC";  // Default sort order

    // Check the selected field for sorting
    if (ui->comboBoxsortchamp_cd->currentText().compare("Date", Qt::CaseInsensitive) == 0) {
        champ = "date_creation";
    } else if (ui->comboBoxsortchamp_cd->currentText().compare("Montant", Qt::CaseInsensitive) == 0) {
        champ = "montant_tel";
    }

    // Check the selected order
    if (ui->comboBox_order_cd->currentText().compare("Descendant", Qt::CaseInsensitive) == 0) {
        order = "DESC";
    }

    qDebug() << "Order:" << order;
    qDebug() << "Champ:" << champ;

    // Update the table view model with sorted data
    ui->tableView_commande->setModel(commande.Tri(order, champ));
}





void MainWindow::on_tableView_commande_doubleClicked(const QModelIndex &index)
{
    // Get the selected row
    int row = index.row();

    // Retrieve the data from each column of the selected row
    int id = ui->tableView_commande->model()->index(row, 0).data().toInt();
    QDate date_creation = ui->tableView_commande->model()->index(row, 1).data().toDate();
    QString statut = ui->tableView_commande->model()->index(row, 2).data().toString();
    int quantite = ui->tableView_commande->model()->index(row, 3).data().toInt();
    int montant_total = ui->tableView_commande->model()->index(row, 4).data().toInt();

    // Populate the form fields with the retrieved data
    ui->idCommande->setText(QString::number(id));
    ui->dateEdit_date->setDate(date_creation);
    ui->comboBox_satut->setCurrentText(statut);
    ui->lineEdit_quantite->setText(QString::number(quantite));
    ui->lineEdit_montant->setText(QString::number(montant_total));
}





void MainWindow::on_lineEdit_textChanged( QString text)
{
    QSqlQueryModel* resultModel = Commande::rechercherParStatut(text);

    if (resultModel) {
        ui->tableView_commande->setModel(resultModel);
    } else {
        // Gérer l'erreur, par exemple afficher un message d'erreur
        QMessageBox::critical(this, "Erreur de recherche", "Une erreur s'est produite lors de la recherche.");
    }
}



void MainWindow::on_dateEdit_recherche_dateChanged(const QDate &date)
{
    // Create an instance of the Formation class
    Commande commande;

    // Call the function to search formations by journee
    QSqlQueryModel* model = commande.rechercherParDateCreation(date);

    // Set the model to the QTableView
    ui->tableView_commande->setModel(model);
}


void MainWindow::generatePDF( QString filePath)
{
    // Get the file path using QFileDialog
    QString fileName = filePath;
    if (fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath(), "PDF Files (*.pdf)");
    }

    // Check if the user canceled the dialog or didn't provide a file name
    if (fileName.isNull()) {
        qDebug() << "PDF generation canceled by the user.";
        return;
    }

    // Create a PDF writer
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A1));

    // Create a painter for the PDF
    QPainter painter(&pdfWriter);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Retrieve data from the table view model and write it to the PDF
    int rowCount = ui->tableView_commande->model()->rowCount();
    int colCount = ui->tableView_commande->model()->columnCount();
    int cellWidth = pdfWriter.width() / colCount;
    int cellHeight = 500;
    int margin = 100;


    QFont font = painter.font();
    font.setPixelSize(200);
    painter.setFont(font);

    // Draw headers
    for (int col = 0; col < colCount; ++col) {
        QString headerData = ui->tableView_commande->model()->headerData(col, Qt::Horizontal).toString();
        int x = col * cellWidth + margin;
        int y = 0;
        QRect headerRect(x, y, cellWidth - margin, cellHeight - margin);
        painter.drawText(headerRect, Qt::AlignLeft | Qt::AlignVCenter, headerData);
    }

    // Draw cell data
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QModelIndex index = ui->tableView_commande->model()->index(row, col);
            QString cellData = ui->tableView_commande->model()->data(index, Qt::DisplayRole).toString();

            // Calculate cell position with padding
            int x = col * cellWidth + margin;
            int y = (row + 1) * cellHeight + margin;

            // Draw cell data with padding
            QRect cellRect(x, y, cellWidth - margin, cellHeight - margin);
            painter.drawText(cellRect, Qt::AlignLeft | Qt::AlignVCenter, cellData);
        }
    }

    // Finish painting
    painter.end();

    QMessageBox::information(this, "PDF Generated", "PDF generated successfully at:\n" + fileName);
}


void MainWindow::displayCommandeStat() {
    // Create a QVBoxLayout for ui->frame_cd if it doesn't have a layout
    if (!ui->frame_cd->layout()) {
        QVBoxLayout *frameLayout = new QVBoxLayout(ui->frame_cd);
        ui->frame_cd->setLayout(frameLayout);
    }

    // Clear any existing widgets in the QFrame
    QLayoutItem *item;
    while ((item = ui->frame_cd->layout()->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    // Retrieve the data to be displayed in the bar chart
    Commande commande;
    QBarSeries *series = commande.getStatStatut();

    if (!series) {
        qDebug() << "Failed to retrieve statistics data from the database.";
        return;
    }

    // Create the bar chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage des commandes par statut");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Create the category axis (X-axis)
    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->setTitleText("Statut");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Create the value axis (Y-axis)
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Pourcentage");
    axisY->setRange(0, 100); // Since it's a percentage
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing, true);

    // Adjust the size of the chart view
    chartView->setFixedSize(721, 281);

    // Add the chart view to the layout of the parent widget
    ui->frame_cd->layout()->addWidget(chartView);
}




//fonction pour recuperer le client qui a la commande celle ci

void MainWindow::populateClientComboBox() {
    ui->comboBox_client->clear();
    QSqlQuery query("SELECT id, nom FROM client");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        ui->comboBox_client->addItem(name, id);
    }
}



void MainWindow::sendOrderConfirmationSMS() {
    // Retrieve the last inserted order ID by selecting the highest ID from the commande table
    QSqlQuery query;
    query.prepare("SELECT c.nom, c.num_tel, cm.date_creation, cm.montant_tel, cm.statut "
                  "FROM client c "
                  "JOIN commande cm ON c.id = cm.id_client "
                  "WHERE cm.id = (SELECT MAX(id) FROM commande)");
    if (!query.exec()) {
        qDebug() << "Failed to retrieve the latest order and client details:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString clientName = query.value("nom").toString();
        QString clientPhoneNumber = query.value("num_tel").toString();
        QString dateCreation = query.value("date_creation").toDate().toString("dd/MM/yyyy");
        QString montantTotal = query.value("montant_tel").toString();
        QString statut = query.value("statut").toString().trimmed();  // Trim whitespace from statut

        // Format the phone number with Tunisian country code
        QString tunisianPhoneNumber = "+216" + clientPhoneNumber;

        // Create the SMS confirmation message content
        QString message;
        if (statut == "Confirmee") {
            message = QString("Bonjour %1,\n\n"
                              "Votre commande du %2 a été confirmée avec succès.\n"
                              "Montant total : %3 TND.\n\n"
                              "Merci pour votre confiance,\n"
                              "L'équipe de gestion des commandes.")
                          .arg(clientName)
                          .arg(dateCreation)
                          .arg(montantTotal);
        } else if (statut == "Annulee") {
            message = QString("Bonjour %1,\n\n"
                              "Nous regrettons de vous informer que votre commande du %2 a été annulée.\n"
                              "Montant total : %3 TND.\n\n"
                              "Merci pour votre compréhension,\n"
                              "L'équipe de gestion des commandes.")
                          .arg(clientName)
                          .arg(dateCreation)
                          .arg(montantTotal);
        } else if (statut == "En attente") {
            message = QString("Bonjour %1,\n\n"
                              "Votre commande du %2 est en attente de confirmation.\n"
                              "Montant total : %3 TND.\n\n"
                              "Nous vous tiendrons informé de l'évolution,\n"
                              "L'équipe de gestion des commandes.")
                          .arg(clientName)
                          .arg(dateCreation)
                          .arg(montantTotal);
        } else {
            // Fallback message if statut does not match known values
            message = QString("Bonjour %1,\n\n"
                              "Détails de votre commande du %2.\n"
                              "Montant total : %3 TND.\n\n"
                              "Merci, L'équipe de gestion des commandes.")
                          .arg(clientName)
                          .arg(dateCreation)
                          .arg(montantTotal);
        }

        // Check if phone number or message is empty
        if (tunisianPhoneNumber.trimmed().isEmpty() || message.trimmed().isEmpty()) {
            qDebug() << "Error: Phone number or message content is empty!";
            qDebug() << "Phone number:" << tunisianPhoneNumber;
            qDebug() << "Message:" << message;
            return;
        }

        // Send the SMS using Twilio or another SMS service
        sendSMS(tunisianPhoneNumber, message);
    }
}

void MainWindow::sendSMS(const QString& to, const QString& message) {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    // Corrected URL
    QUrl url("https://api.twilio.com/2010-04-01/Accounts/AC1b15ad8fbabb3852934c54eaf662d8a4/Messages.json");
    QNetworkRequest request(url);

    // Set the content type header
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Prepare the authorization header
    QString auth = "AC1b15ad8fbabb3852934c54eaf662d8a4:93dda7df1796a444e74cea4d5630d63a";
    QByteArray authData = auth.toLocal8Bit().toBase64();
    request.setRawHeader("Authorization", "Basic " + authData);

    // Prepare the parameters
    QUrlQuery params;
    params.addQueryItem("From", "+15052278899");  // Your Twilio phone number
    params.addQueryItem("To", to);                // Recipient's phone number
    params.addQueryItem("Body", message);         // SMS content

    // Encode the parameters
    QByteArray data = params.toString(QUrl::FullyEncoded).toUtf8();

    // Connect to handle the reply
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        // Check the HTTP status code
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if (statusCode.isValid()) {
            qDebug() << "HTTP Status Code:" << statusCode.toInt();
        } else {
            qDebug() << "No HTTP status code received.";
        }

        // Log the raw response from the server
        QByteArray response = reply->readAll();
        qDebug() << "Response from Twilio:" << response;

        // Check for errors
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "SMS sent successfully!";
        } else {
            qDebug() << "SMS sending failed:" << reply->errorString();
            qDebug() << "Error code:" << reply->error();
        }

        reply->deleteLater();
    });

    // Send the POST request
    manager->post(request, data);

    // Log that the request was sent
    qDebug() << "POST request sent.";
}














void MainWindow::highlightOrderDates()
{
    // Create a map to store dates that have orders
    QMap<QDate, QColor> orderDates;

    // Fetch unique order dates from the database
    QSqlQuery query;
    query.prepare("SELECT DISTINCT date_creation FROM commande");

    if (!query.exec()) {
        qDebug() << "Failed to retrieve order dates:" << query.lastError().text();
        return;
    }

    // Loop through the results and add each date to the map
    while (query.next()) {
        QDate orderDate = query.value(0).toDate();
        orderDates.insert(orderDate, Qt::green);  // Use any color you prefer, e.g., green
    }

    // Update the calendar to highlight these dates
    QCalendarWidget *calendar = ui->calendarWidget_cd;
    calendar->setDateTextFormat(QDate(), QTextCharFormat());  // Reset all formatting

    // Iterate through the map and apply the format
    QTextCharFormat format;
    format.setBackground(Qt::yellow);  // Set the background color for days with orders
    for (auto it = orderDates.begin(); it != orderDates.end(); ++it) {
        calendar->setDateTextFormat(it.key(), format);
    }

    // Log that the dates have been highlighted
    qDebug() << "Order dates highlighted in the calendar.";
}


void MainWindow::on_calendarWidget_cd_selectionChanged()
{
    // Get the selected date from the calendar
    QDate selectedDate = ui->calendarWidget_cd->selectedDate();
    QString formattedDate = selectedDate.toString("dd-MMM-yy").toUpper();

    // Log the selected date for debugging
    qDebug() << "Selected Date:" << formattedDate;

    // Fetch the orders created on the selected date from the 'commande' table
    QSqlQuery query;
    query.prepare("SELECT c.nom, c.num_tel, cm.date_creation, cm.montant_tel, cm.statut, cm.quantite "
                  "FROM client c "
                  "JOIN commande cm ON c.id = cm.id_client "
                  "WHERE TO_CHAR(cm.date_creation, 'DD-MON-YY') = :selected_date");

    query.bindValue(":selected_date", formattedDate);

    // Log the query being executed for debugging
    qDebug() << "Executing query:" << query.lastQuery();

    if (!query.exec()) {
        qDebug() << "Failed to retrieve orders for selected date:" << query.lastError().text();
        return;
    }
    highlightOrderDates();

    // Log the number of rows retrieved for debugging
    int rowCount = query.size();
    qDebug() << "Number of rows retrieved:" << rowCount;

    // Create a model to display the data in the QTableView
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(std::move(query));

    // Log the number of rows in the model
    qDebug() << "Rows in the model:" << model->rowCount();

    // Set headers for the table
    model->setHeaderData(0, Qt::Horizontal, "Client Name");
    model->setHeaderData(1, Qt::Horizontal, "Phone Number");
    model->setHeaderData(2, Qt::Horizontal, "Order Date");
    model->setHeaderData(3, Qt::Horizontal, "Total Amount");
    model->setHeaderData(4, Qt::Horizontal, "Status");
    model->setHeaderData(5, Qt::Horizontal, "Quantity");

    // Display the data in a table view
    ui->tableView_commande->setModel(model);
    ui->tableView_commande->resizeColumnsToContents();
}


void MainWindow::on_back_clicked()
{
    ui->stackedWidgetprincipale->setCurrentIndex(2);
}


void MainWindow::on_pushButton_5_clicked()
{
    // Navigate to the relevant page in the stacked widget
    int pageIndex = ui->stackedWidgetprincipale->indexOf(ui->page_3);
    ui->stackedWidgetprincipale->setCurrentIndex(pageIndex);

    // Display the statistics directly
      updateStatistics();

    // Fetch and display client records in the table
    Client client;
    QSqlQueryModel *model = client.afficher();  // Assuming afficher() fetches client data
    ui->tableView->setModel(model);  // Set the model to the tableView

    // Adjust table appearance if necessary
    ui->tableView->verticalHeader()->setDefaultSectionSize(80);  // Adjust row height
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  // Optional: Stretch columns to fit

    // Refresh all tables and views (if needed)
    refreshAllTablesAndViews();
}


void MainWindow::on_returnclients_clicked()
{
    ui->stackedWidgetprincipale->setCurrentIndex(2);


}


void MainWindow::on_afficheclient_clicked()
{
    Client m1;

    // Passer à la page cible
    ui->stackedWidgetclients->setCurrentIndex(0);

    // Charger les données depuis la base de données
    QSqlQueryModel *model = m1.afficher();

    if (model) {
        // Appliquer le modèle au QTableView
        ui->tableView->setModel(model);

        // Forcer un rafraîchissement de la vue
        ui->tableView->reset();  // Ceci peut aider à forcer la mise à jour de la vue

        // Ajuster la taille des lignes
        ui->tableView->verticalHeader()->setDefaultSectionSize(80);

        // Appliquer le délégué à la colonne PHOTO
        ImageDelegate *imageDelegate = new ImageDelegate(this);
        ui->tableView->setItemDelegateForColumn(6, imageDelegate);  // Assurez-vous que 6 correspond à la colonne PHOTO
    } else {
        qDebug() << "Erreur de récupération des données pour afficher le modèle.";
    }
    refreshAllTablesAndViews();
}


void MainWindow::on_ajouteclients_clicked()
{
    Client m1;

    // Afficher la page 2 avec le tableau
    ui->stackedWidgetclients->setCurrentIndex(1);

    // Charger les données du modèle depuis la base de données
    QSqlQueryModel *model = m1.afficher();  // Charger les données à partir de la base

    if (model) {
        // Appliquer le modèle au QTableView
        ui->tableView->setModel(model);

        // Appliquer le délégué pour afficher les images dans la colonne "PHOTO" (colonne 6)
        ImageDelegate *imageDelegate = new ImageDelegate(this);
        ui->tableView->setItemDelegateForColumn(6, imageDelegate);  // Assurez-vous que la colonne 6 est la colonne PHOTO

        // Définir la largeur de la colonne PHOTO à 100px
        ui->tableView->setColumnWidth(6, 100);

        // Ajuster la hauteur des lignes automatiquement selon le contenu (ex. taille des images)
        ui->tableView->resizeRowsToContents();  // Dynamically adjust row height based on content, including images

    } else {
        qDebug() << "Erreur lors de la récupération des données pour tableView.";
    }

    // Rafraîchir toutes les vues et autres éléments si nécessaire
    refreshAllTablesAndViews();

     //Assurez-vous que la scène du graphique est correctement définie
    if (scene) {
        ui->graphicsView->setScene(scene);  // Appliquer la scène au graphicsView
   } else {
        qDebug() << "La scène n'est pas définie.";
    }

}


void MainWindow::on_modeferclients_clicked()
{

    Client m1;

    // 1. Changer de page pour la page 3 (vue cible)
    ui->stackedWidgetclients->setCurrentIndex(2);

    // 2. Charger les données du modèle
    QSqlQueryModel *model = m1.afficher();  // Charger les données depuis la base de données

    if (model) {
        // 3. Appliquer le modèle à tableView
        ui->tableView->setModel(model);  // Appliquer le modèle au QTableView

        // 4. Appliquer un délégué d'image pour la colonne PHOTO
        ImageDelegate *imageDelegate = new ImageDelegate();
        ui->tableView->setItemDelegateForColumn(6, imageDelegate);  // Appliquer le délégué à la colonne "PHOTO"

        // 5. Ajuster la hauteur des lignes (facultatif selon besoin)
        ui->tableView->verticalHeader()->setDefaultSectionSize(80);  // Hauteur des lignes à 80px

        // 6. Rafraîchir la vue
        ui->tableView->reset();  // Force un rafraîchissement de la vue
    } else {
        // Si le modèle est vide ou n'a pas pu être récupéré
        qDebug() << "Erreur lors de la récupération des données pour tableView.";
    }

    // 7. Actualiser toutes les vues si nécessaire
   refreshAllTablesAndViews();
}


void MainWindow::on_supprimelesclients_clicked()
{

    Client m1;

    // Charger la page 4
    ui->stackedWidgetclients->setCurrentIndex(3);

    // Charger le modèle dans tableView
    QSqlQueryModel *model = m1.afficher();  // Charger les données depuis la base de données

    if (model) {
        ui->tableView->setModel(model);  // Appliquer le modèle au QTableView
        ui->tableView->verticalHeader()->setDefaultSectionSize(80);
        // Appliquer le délégué pour afficher les images dans la colonne PHOTO
        ImageDelegate *imageDelegate = new ImageDelegate();
        ui->tableView->setItemDelegateForColumn(6, imageDelegate);  // Colonne "PHOTO"
    }

    // Actualiser toutes les vues si nécessaire
    refreshAllTablesAndViews();
}


void MainWindow::on_parametreclients_clicked()
{

    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(4);
}


void MainWindow::on_afficheclients2_clicked()
{
    // Créer un objet Client
    Client m1;

    // 1. Changer de page pour afficher la page souhaitée
    ui->stackedWidgetclients->setCurrentIndex(0);  // Passer à la page souhaitée

    // 2. Récupérer le modèle pour la table et l'afficher dans tableView_2
    QSqlQueryModel* model = m1.afficher();
    if (model) {
        // Appliquer le modèle à tableView_2
        ui->tableView_2->setModel(model);

        // Appliquer un délégué pour afficher les images correctement dans la colonne "PHOTO"
        ImageDelegate *imageDelegate = new ImageDelegate(this);
        ui->tableView_2->setItemDelegateForColumn(6, imageDelegate);  // Assurez-vous que 6 est bien la colonne "PHOTO"
    } else {
        qDebug() << "Erreur: Impossible de récupérer les données du modèle.";
    }

    // 3. Ajuster la hauteur des lignes du tableau
    ui->tableView_2->verticalHeader()->setDefaultSectionSize(80);  // Hauteur des lignes (80px)

    // 4. Récupérer les statistiques sur le sexe et mettre à jour le graphique
    QPair<int, int> statistics = m1.getSexeStatistics();  // Obtenir les statistiques du sexe (par exemple, Homme/Femme)
   // updateSexeCycle(statistics.first, statistics.second);  // Mettre à jour le graphique avec les données de sexe

    // 5. Mettre à jour le graphique dans graphicsView (si nécessaire)
    // Assurez-vous que la scène est bien présente avant de la mettre à jour
    if (ui->graphicsView->scene()) {
        // Ici, vous pouvez soit réinitialiser la scène, soit juste mettre à jour les éléments graphiques
        ui->graphicsView->setScene(ui->graphicsView->scene());  // Réinitialiser ou mettre à jour la scène si nécessaire
    } else {
        qDebug() << "Aucune scène trouvée dans graphicsView.";
    }
    refreshAllTablesAndViews();
}


void MainWindow::on_ajouteclients2_clicked()
{
    Client m1;

    // Charger la page 2
    ui->stackedWidgetclients->setCurrentIndex(1);

    // Charger le modèle dans tableView_2
    QSqlQueryModel *model = m1.afficher();  // Charger les données

    if (model) {
        ui->tableView_2->setModel(model);  // Appliquer le modèle au QTableView
        ui->tableView_2->verticalHeader()->setDefaultSectionSize(80);
        // Appliquer le délégué pour afficher les images
        ImageDelegate *imageDelegate = new ImageDelegate();
        ui->tableView_2->setItemDelegateForColumn(6, imageDelegate);  // Colonne "PHOTO"
    }
    refreshAllTablesAndViews();
}




void MainWindow::on_modeferclinets2_clicked()
{
    // Créer une instance de Client pour accéder aux données
    Client m1;

    // 1. Changer de page pour la page_3 (vue cible)
    ui->stackedWidgetclients->setCurrentIndex(2);

    // 2. Récupérer les données du modèle
    QSqlQueryModel* model = m1.afficher();  // Appel de la méthode afficher() pour obtenir les données

    if (model) {
        // 3. Appliquer le modèle à tableView_2
        ui->tableView_2->setModel(model);

        // 4. Appliquer un délégué d'image si nécessaire
        // Exemple : appliquer un délégué à la colonne "PHOTO" si nécessaire
        ImageDelegate *imageDelegate = new ImageDelegate(this);
        ui->tableView_2->setItemDelegateForColumn(6, imageDelegate);  // La colonne "PHOTO" est l'index 6

        // 5. Ajuster la hauteur des lignes à 80px
        ui->tableView_2->verticalHeader()->setDefaultSectionSize(80);

        // 6. Rafraîchir la vue pour s'assurer que tout est correctement affiché
        ui->tableView_2->reset();  // Force un rafraîchissement de la vue

    } else {
        // Si le modèle est vide ou n'a pas pu être récupéré
        qDebug() << "Erreur lors de la récupération des données pour tableView_2.";
    }
}

void MainWindow::refreshAllTablesAndViews() {
    Client client;

    // Récupérer les statistiques des sexes avant de rafraîchir les vues
    QPair<int, int> statistics = client.getSexeStatistics();
    int maleCount = statistics.first;
    int femaleCount = statistics.second;

    // Mettre à jour le QLabel avec les statistiques des sexes
    QString statisticsText = QString("Hommes: %1\nFemmes: %2").arg(maleCount).arg(femaleCount);
    ui->labelSexeStats->setText(statisticsText);  // Affichez les résultats dans un QLabel

    // Rafraîchir chaque table avec les données les plus récentes
    ui->tableView->setModel(client.afficher());
    ui->tableView_2->setModel(client.afficher());
    ui->tableView_3->setModel(client.afficher());
    ui->tableView_4->setModel(client.afficher());

    // Rafraîchir chaque comboBox avec les données les plus récentes
    ui->comboBox->setModel(client.afficher());
    ui->comboBox_2->setModel(client.afficher());

    // Rafraîchir le délégué d'image pour la colonne "PHOTO" sur chaque table
    ImageDelegate *imageDelegate = new ImageDelegate();
    ui->tableView->setItemDelegateForColumn(6, imageDelegate);  // Assurez-vous que cela est appliqué à la bonne table
    ui->tableView_2->setItemDelegateForColumn(6, imageDelegate);
    ui->tableView_3->setItemDelegateForColumn(6, imageDelegate);
    ui->tableView_4->setItemDelegateForColumn(6, imageDelegate);


}
void MainWindow::on_supprimeclients2_clicked()
{
    Client m1;

    // Charger la page 4
    ui->stackedWidgetclients->setCurrentIndex(3);

    // Charger le modèle dans tableView_2
    QSqlQueryModel *model = m1.afficher();  // Charger les données depuis la base de données

    if (model) {
        ui->tableView_2->setModel(model);  // Appliquer le modèle au QTableView
        ui->tableView_2->verticalHeader()->setDefaultSectionSize(80);
        // Appliquer le délégué pour afficher les images dans la colonne PHOTO
        ImageDelegate *imageDelegate = new ImageDelegate();
        ui->tableView_2->setItemDelegateForColumn(6, imageDelegate);  // Colonne "PHOTO"
    }

    // Actualiser toutes les vues si nécessaire
    refreshAllTablesAndViews();
}


void MainWindow::on_parametreclients_2_clicked()
{

    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(4);
}


void MainWindow::on_afficheclients3_clicked()
{
    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(0);

    ui->tableView_3->setModel(m1.afficher());
    QPair<int, int> statistics = m1.getSexeStatistics();  // Get updated male/female stats
   /// updateSexeCycle(statistics.first, statistics.second);  // Update the cycle chart
    ui->tableView_3->verticalHeader()->setDefaultSectionSize(80);
    // No need to call show() for graphicsView; it should already be visible if part of the layout
    ui->graphicsView->setScene(ui->graphicsView->scene());  // Ensure graphicsView shows
}


void MainWindow::on_ajouteclients3_clicked()
{
    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(1);

    // Charger les données depuis la base de données
    QSqlQueryModel* model = m1.afficher();

    if (model) {
        // Appliquer le modèle à tableView_3
        ui->tableView_3->setModel(model);

        // Appliquer un délégué d'image pour la colonne PHOTO (colonne 6, à adapter si nécessaire)
        ImageDelegate *imageDelegate = new ImageDelegate(this);
        ui->tableView_3->setItemDelegateForColumn(6, imageDelegate);  // Assurez-vous que la colonne PHOTO est bien la 6

        // Ajuster la hauteur des lignes à 80px
        ui->tableView_3->verticalHeader()->setDefaultSectionSize(80);
    } else {
        qDebug() << "Erreur lors de la récupération des données pour tableView_3.";
    }
}


void MainWindow::on_moddeferclients3_clicked()
{
    Client m1;

    // Charger la page 3
    ui->stackedWidgetclients->setCurrentIndex(2);

    // Charger le modèle dans tableView_3
    QSqlQueryModel *model = m1.afficher();  // Charger les données

    if (model) {
        ui->tableView_3->setModel(model);  // Appliquer le modèle au QTableView
        ui->tableView_3->verticalHeader()->setDefaultSectionSize(80);
        // Appliquer le délégué pour afficher les images
        ImageDelegate *imageDelegate = new ImageDelegate();
        ui->tableView_3->setItemDelegateForColumn(6, imageDelegate);  // Colonne "PHOTO"
    }
}


void MainWindow::on_supprimeclients3_clicked()
{
    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(3);
    ui->tableView_3->setModel(m1.afficher()); // Refresh the table view

    ui->tableView_3->verticalHeader()->setDefaultSectionSize(80);

}


void MainWindow::on_parametreclients3_clicked()
{
    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(4);
}


void MainWindow::on_afficheclients4_clicked()
{
    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(0);
    ui->tableView_4->setModel(m1.afficher());
    QPair<int, int> statistics = m1.getSexeStatistics();  // Get updated male/female stats
   // updateSexeCycle(statistics.first, statistics.second);  // Update the cycle chart
    ui->tableView_4->verticalHeader()->setDefaultSectionSize(80);
    // No need to call show() for graphicsView; it should already be visible if part of the layout
    ui->graphicsView->setScene(ui->graphicsView->scene());  // Ensure graphicsView shows
}


void MainWindow::on_ajouteclients4_clicked()
{
    Client m1;
    ui->tableView_4->verticalHeader()->setDefaultSectionSize(80);
    ui->stackedWidgetclients->setCurrentIndex(1);
    ui->tableView_4->setModel(m1.afficher());
}


void MainWindow::on_modeferclients4_clicked()
{
    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(2);
    ui->tableView_4->setModel(m1.afficher());
    ui->tableView_4->verticalHeader()->setDefaultSectionSize(80);
}


void MainWindow::on_supprimeclients4_clicked()
{
    Client m1;

    // Afficher la page correspondante
     ui->stackedWidgetclients->setCurrentIndex(3);

    // Obtenir le modèle de données
    QSqlQueryModel *model = m1.afficher();

    if (model) {
        ui->tableView_4->setModel(model);

        // Appliquer le délégué pour la colonne des images
        ImageDelegate *imageDelegate = new ImageDelegate(this);
        ui->tableView_4->setItemDelegateForColumn(6, imageDelegate); // Colonne 6 pour les images

        // Augmenter la hauteur des lignes
        ui->tableView_4->verticalHeader()->setDefaultSectionSize(80);

        // Ajuster la largeur de la colonne contenant les images
        ui->tableView_4->setColumnWidth(6, 100);
    }
}


void MainWindow::on_parametreclients4_clicked()
{
    Client m1;
     ui->stackedWidgetclients->setCurrentIndex(4);
}





void MainWindow::on_afficheclients4_2_clicked()
{
    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(0);
    QPair<int, int> statistics = m1.getSexeStatistics();  // Get updated male/female stats
   // updateSexeCycle(statistics.first, statistics.second);  // Update the cycle chart

    // No need to call show() for graphicsView; it should already be visible if part of the layout
    ui->graphicsView->setScene(ui->graphicsView->scene());  // Ensure graphicsView shows
}


void MainWindow::on_ajjouteclinets4_clicked()
{
    Client m1;
     ui->stackedWidgetclients->setCurrentIndex(1);
}


void MainWindow::on_modeferclients4_2_clicked()
{
    Client m1;
     ui->stackedWidgetclients->setCurrentIndex(2);
}


void MainWindow::on_supprimeclients4_2_clicked()
{

    Client m1;
    ui->stackedWidgetclients->setCurrentIndex(3);
}


void MainWindow::on_parametre4_clicked()
{

}

    void MainWindow::updateSexeCycle(int maleCount, int femaleCount) {
        int total = maleCount + femaleCount;
        if (total == 0) {
            qDebug() << "Total des clients égal à zéro, aucun graphique à afficher.";
            return;  // Eviter la division par zéro
        }

        // Accédez à la scène actuelle
        QGraphicsScene *scene = ui->graphicsView->scene();
        if (!scene) {
            scene = new QGraphicsScene();
            ui->graphicsView->setScene(scene);  // Créez une nouvelle scène si elle n'existe pas
        } else {
            scene->clear();  // Effacez la scène existante pour éviter l'empilement des anciens graphiques
        }

        int radius = 100;  // Rayon du cercle
        int centerX = 10; // Position X du centre
        int centerY = 5; // Position Y du centre

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

        // Ajouter le pourcentage des hommes
        QString malePercentage = QString::number((maleCount * 100.0) / total, 'f', 1) + "%";
        QGraphicsTextItem *maleText = new QGraphicsTextItem(malePercentage);
        maleText->setFont(QFont("Arial", 17, QFont::Bold));  // Set the font to bold
        maleText->setDefaultTextColor(Qt::black);  // Set text color to blue
        maleText->setPos(centerX + radius * qCos(qDegreesToRadians(90 - maleAngle / 2)) - maleText->boundingRect().width() / 2,
                         centerY - radius * qSin(qDegreesToRadians(90 - maleAngle / 2)) - maleText->boundingRect().height() / 2);
        scene->addItem(maleText);

        // Ajouter le pourcentage des femmes
        QString femalePercentage = QString::number((femaleCount * 100.0) / total, 'f', 1) + "%";
        QGraphicsTextItem *femaleText = new QGraphicsTextItem(femalePercentage);
        femaleText->setFont(QFont("Arial", 17, QFont::Bold));  // Set the font to bold
        femaleText->setDefaultTextColor(Qt::red);  // Set text color to red
        femaleText->setPos(centerX + radius * qCos(qDegreesToRadians(90 - maleAngle - femaleAngle / 2)) - femaleText->boundingRect().width() / 2,
                           centerY - radius * qSin(qDegreesToRadians(90 - maleAngle - femaleAngle / 2)) - femaleText->boundingRect().height() / 2);
        scene->addItem(femaleText);

        // Mettre à jour l'affichage dans le graphicsView
        ui->graphicsView->setScene(scene);
    }

    void MainWindow::updateStatistics()
    {
        // Fetch the latest data from the Client class
        Client client;
        QPair<int, int> statistics = client.getSexeStatistics(); // Example: Returns a QPair of male and female counts

        int maleCount = statistics.first;
        int femaleCount = statistics.second;

        // Log the fetched counts for debugging
        qDebug() << "Male Count:" << maleCount << "Female Count:" << femaleCount;

        // Update the chart with the fetched data
        updateSexeCycle(maleCount, femaleCount);
    }

    void MainWindow::on_updateStatisticsButton_clicked()
    {
        updateStatistics(); // Update the chart when the button is clicked
    }

void MainWindow::on_recherche_textChanged(const QString &text) {
    Client client;
    QSqlQueryModel *model = client.search(text); // Use the search method in Client class

    if (model) {
        ui->tableView->setModel(model); // Assuming your table view is named 'tableView'
        //ui->tableView->verticalHeader()->setDefaultSectionSize(80);
    }
    // ui->tableView->verticalHeader()->setDefaultSectionSize(80);
}


void MainWindow::on_trierParNom_clicked() {
    Client client;
    QSqlQueryModel *model = client.trierParNom(); // Appel de la méthode pour trier par nom

    if (model) {
        ui->tableView->setModel(model); // Mettre à jour la vue avec les résultats triés
    }
}

void MainWindow::on_ajouteunclients_clicked()
{
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    int num_tel = ui->numtel->text().toInt();
    int age = ui->age->text().toInt();

    // Determine the gender based on the selected radio button
    QString sexe;
    if (ui->homme->isChecked()) {
        sexe = "Homme";
    } else if (ui->femme->isChecked()) {
        sexe = "Femme";
    } else {
        sexe = "Autre";
    }

    // Create the client with the image path
    Client client(id, nom, prenom, sexe, num_tel, age);
    client.setPhotoPath(currentImagePath); // Set the image path for the client

    // Try to create the client in the database
    if (client.create()) {
        QMessageBox::information(this, "Success", "Client created successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to create client.");
    }

    // Reset the gender selection
    ui->homme->setChecked(true);

    // Refresh the view with the updated data
    QSqlQueryModel *model = client.afficher();
    ui->tableView_2->setModel(model); // Set the model with updated data

    // Apply the image delegate to the table view column (PHOTO column is usually column 6)
    ImageDelegate *imageDelegate = new ImageDelegate(this);
    ui->tableView_2->setItemDelegateForColumn(6, imageDelegate); // Apply the delegate to the image column

    refreshAllTablesAndViews();  // Optional: Refresh all tables and views
     updateStatistics();
}




void MainWindow::on_modefieruclients_clicked()
{
    // Récupérer l'ID du client à partir de comboBox
    Client client;
    int clientId = ui->comboBox->currentText().toInt();
    client.setIdClients(clientId);  // Assurez-vous que l'ID du client est correct

    // Récupérer les nouvelles valeurs des champs de saisie
    QString nom = ui->nom_2->text();
    QString prenom = ui->prenom_2->text();
    int num_tel = ui->numtel_2->text().toInt();
    int age = ui->age_2->text().toInt();

    // Déterminer le sexe mis à jour en fonction du bouton radio sélectionné
    QString sexe;
    if (ui->homme_2->isChecked()) {
        sexe = "Homme";
    } else if (ui->femme_2->isChecked()) {
        sexe = "Femme";
    } else {
        sexe = "Autre"; // Si nécessaire, gérer les autres cas
    }

    // Mettre à jour les informations du client
    client.nom = nom;
    client.prenom = prenom;
    client.sexe = sexe;
    client.num_tel = num_tel;
    client.age = age;

    // Tenter de mettre à jour le client dans la base de données
    if (client.update()) {
        QMessageBox::information(this, "Succès", "Client mis à jour avec succès.");

        // Rafraîchir la table pour afficher les nouvelles informations
        QSqlQueryModel *model = client.afficher();
        if (model) {
            ui->tableView_3->setModel(model);  // Rafraîchir la table
            ui->comboBox->setModel(model);     // Rafraîchir le comboBox
        }
        refreshAllTablesAndViews();  // Rafraîchir toutes les vues
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour du client.");
    }
     updateStatistics();
}


void MainWindow::on_supprimeunclients_clicked()
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
     updateStatistics();
}


void MainWindow::envoyerWhatsApp(const QString &numeroClient){
    QString accountSID = "ACa29d9d63a35f09ba0ad329512b1bd5ba";  // SID de votre compte Twilio
    QString authToken = "5fa08d06278fd5343e5ba636c76264ef";  // Votre AuthToken Twilio
    QString from = "+19548668753";  // Votre numéro Twilio
    QString body = "Merci beaucoup pour votre achat ! Nous espérons vous revoir bientôt."; // Message de remerciement

    QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + accountSID + "/Messages.json");

    // Paramètres de la requête
    QUrlQuery params;
    params.addQueryItem("To", numeroClient);  // Numéro du destinataire
    params.addQueryItem("From", from);  // Votre numéro Twilio
    params.addQueryItem("Body", body);  // Contenu du message

    // Préparation de la requête
    QNetworkRequest request(url);
    QByteArray authData = (accountSID + ":" + authToken).toUtf8();
    QByteArray base64AuthData = authData.toBase64();
    QString authHeader = "Basic " + authData.toBase64();
    request.setRawHeader("Authorization", authHeader.toUtf8());
    request.setRawHeader("Authorization", "Basic " + base64AuthData);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Envoi de la requête POST
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());

    // Connexion pour gérer la réponse
    connect(reply, &QNetworkReply::finished, this, &MainWindow::onNotificationSent);
}

void MainWindow::on_notification_sms_clicked() {
    QString numeroClient = ui->numero_client->text();  // Récupérer le texte du QLineEdit
    if (numeroClient.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un numéro de client.");
        return;
    }
    envoyerWhatsApp(numeroClient);
}

void MainWindow::onNotificationSent() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();

        // Décodez la réponse JSON
        QJsonDocument doc = QJsonDocument::fromJson(response);
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            QString status = obj["status"].toString();
            if (status == "queued") {
                QMessageBox::information(this, "Notification", "Le message est en file d'attente et sera envoyé bientôt.");
            } else {
                QMessageBox::information(this, "Notification", "Le message a été envoyé avec succès.");
            }
        } else {
            QMessageBox::warning(this, "Erreur", "La réponse n'est pas au format JSON attendu.");
        }
    } else {
        // Affichez les détails de l'erreur retournée par Twilio
        QString errorMsg = reply->errorString();
        QString responseText = reply->readAll();
        qDebug() << "Erreur Twilio:" << errorMsg;
        qDebug() << "Réponse complète Twilio:" << responseText;

        // Affichage de l'erreur détaillée dans une boîte de dialogue
        QMessageBox::warning(this, "Erreur", "L'envoi du message a échoué : " + errorMsg + "\nRéponse : " + responseText);
    }
    reply->deleteLater();
}


void MainWindow::exporterPDF() {
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

    // Charger l'image depuis les ressources
    QPixmap logo(":/images/im.png");
    if (!logo.isNull()) {
        QRect logoRect(250, 800, 2000, 2000); // Position et taille du logo
        painter.drawPixmap(logoRect, logo);
    } else {
        qDebug() << "Erreur: Impossible de charger l'image du logo.";
    }

    // Polices et paramètres de mise en page
    QFont headerFont("Arial", 10, QFont::Bold);
    QFont cellFont("Arial", 9);
    int xOffset = 50;   // Décalage horizontal du début du tableau
    int yOffset = 50;  // Décalage vertical du début du tableau (après le logo)
    int lineHeight = 150; // Hauteur de chaque ligne du tableau
    int colWidth = 330;  // Largeur de chaque colonne
    int currentY = yOffset;

    // Titre du PDF
    QFont titleFont("Arial", 14, QFont::Bold);
    painter.setFont(titleFont);
    painter.drawText(writer.width() / 2 - 100, currentY, "Liste des Clients");
    currentY += 50; // Espace après le titre

    // Dessiner les en-têtes des colonnes
    painter.setFont(headerFont);
    for (int col = 0; col < model->columnCount(); ++col) {
        QRect headerRect(xOffset + col * colWidth, currentY, colWidth, lineHeight);
        painter.drawText(headerRect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
        painter.drawRect(headerRect); // Encadrer l'en-tête
    }

    currentY += lineHeight; // Passer à la ligne suivante après les en-têtes

    // Dessiner les données
    painter.setFont(cellFont);
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QRect cellRect(xOffset + col * colWidth, currentY, colWidth, lineHeight);
            QString cellData = model->data(model->index(row, col)).toString();
            painter.drawText(cellRect, Qt::AlignCenter, cellData);
            painter.drawRect(cellRect); // Encadrer la cellule
        }
        currentY += lineHeight;

        // Gérer les nouvelles pages si nécessaire
        if (currentY > writer.height() - 100) {
            writer.newPage();
            currentY = yOffset;

            // Redessiner le logo et les en-têtes sur la nouvelle page
            if (!logo.isNull()) {
                QRect logoRect(50, 50, 100, 100);
                painter.drawPixmap(logoRect, logo);
            }

            currentY = yOffset + 50; // Ajuster la position après le logo
            painter.setFont(headerFont);
            for (int col = 0; col < model->columnCount(); ++col) {
                QRect headerRect(xOffset + col * colWidth, currentY, colWidth, lineHeight);
                painter.drawText(headerRect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
                painter.drawRect(headerRect);
            }
            currentY += lineHeight; // Passer à la ligne suivante après les en-têtes
        }
    }

    painter.end();
    QMessageBox::information(this, "Succès", "Le tableau des clients a été exporté avec succès.");
}

void MainWindow::on_lightButton_clicked()
{
     setLightMode();
}


void MainWindow::on_nightButton_clicked()
{
    setNightMode();
}


void MainWindow::on_normal_clicked()
{
    setStyleSheet("");
}


void MainWindow::on_recherch_image_clicked()
{
    // Ouvrir un dialogue de fichier pour choisir une image
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Choisir une image"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

    // Si une image a été sélectionnée
    if (!imagePath.isEmpty()) {
        // Mettre à jour le QLabel pour afficher l'image
        QPixmap pixmap(imagePath);

        if (!pixmap.isNull()) {
            // Afficher l'image dans le QLabel
            ui->recherche_path->setPixmap(pixmap);
            ui->recherche_path->setScaledContents(true);  // Redimensionner l'image pour qu'elle s'adapte au QLabel
        }

        // Rechercher le client en fonction de l'image
        rechercherClientParImage(imagePath);
    }
}
void MainWindow::rechercherClientParImage(const QString &imagePath)
{
    // Créer une instance de Client pour interagir avec la base de données
    Client m1;

    // Préparer une requête SQL pour rechercher l'image dans la base de données
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE PHOTO = :imagePath");
    query.bindValue(":imagePath", imagePath);

    if (query.exec()) {
        if (query.next()) {  // Si l'image est trouvée
            // Récupérer les informations du client depuis la base de données
            int idClient = query.value("ID_CLIENTS").toInt();
            QString nom = query.value("NOM").toString();
            QString prenom = query.value("PRENOM").toString();
            QString sexe = query.value("SEXE").toString();
            int age = query.value("AGE").toInt();
            QString numTel = query.value("NUM_TEL").toString();

            // Afficher les informations dans le QTableView
            QSqlQueryModel *model = new QSqlQueryModel();
            query.prepare("SELECT ID_CLIENTS, NOM, PRENOM, SEXE, AGE, NUM_TEL FROM CLIENT WHERE ID_CLIENTS = :id");
            query.bindValue(":id", idClient);
            if (query.exec()) {
                model->setQuery(query);
                ui->tableView->setModel(model);  // Appliquer le modèle au QTableView

                // Ajuster la hauteur des lignes et la largeur des colonnes
                ui->tableView->verticalHeader()->setDefaultSectionSize(80);
                ui->tableView->setColumnWidth(0, 100);  // ID_CLIENTS
                ui->tableView->setColumnWidth(1, 150);  // NOM
                ui->tableView->setColumnWidth(2, 150);  // PRENOM
                ui->tableView->setColumnWidth(3, 80);   // SEXE
                ui->tableView->setColumnWidth(4, 80);   // AGE
                ui->tableView->setColumnWidth(5, 150);  // NUM_TEL
            }
        } else {
            // Si aucune image n'est trouvée, afficher un message d'erreur ou vider le tableau
            qDebug() << "Aucun client avec cette image trouvée.";
            ui->tableView->setModel(nullptr);  // Vider le tableau
        }
    } else {
        // En cas d'erreur d'exécution de la requête SQL
        qDebug() << "Erreur de requête SQL:" << query.lastError().text();
    }
}

void MainWindow::on_ajoute_image_clicked()
{
    // Open file dialog to select the image
            QString filePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp)");

    if (!filePath.isEmpty()) {
        // Display the image in the QLabel imageLabel_2
        QPixmap pixmap(filePath);
        if (!pixmap.isNull()) {
            ui->imageLabel_2->setPixmap(pixmap);  // Display the image in the QLabel
            ui->imageLabel_2->setScaledContents(true);  // Scale the image to fit the QLabel
        } else {
            QMessageBox::critical(this, "Error", "Failed to load the image.");
        }

        // Save the image path for later use
        currentImagePath = filePath;  // The image path is saved for use later
    }
}
void MainWindow::updateIdField()
{
    // Get the selected item from comboBox_2 (assuming it contains numbers)
    int selectedId = ui->comboBox_2->currentText().toInt();

    // Update id_6 with the selected ID
    ui->id_6->setText(QString::number(selectedId));
}


void MainWindow::on_mofeder_image_clicked()
{
    // Sélectionner une nouvelle image
    QString filePath = QFileDialog::getOpenFileName(this, "Select New Image", "", "Images (*.png *.jpg *.bmp)");

    if (!filePath.isEmpty()) {
        // Récupérer l'ID du client à partir de comboBox (ou un autre champ)
        int clientId = ui->comboBox->currentText().toInt();  // Assurez-vous que l'ID du client est sélectionné dans le comboBox

        // Créer un objet client et récupérer ses informations
        Client client;
        client.setIdClients(clientId);  // Définir l'ID du client

        // Mettre à jour l'image du client avec le nouveau chemin
        client.setPhotoPath(filePath);  // Mettre à jour le chemin de l'image du client

        // Mettre à jour la base de données avec la nouvelle image
        if (client.updateImage()) {
            QMessageBox::information(this, "Succès", "L'image du client a été mise à jour avec succès.");

            // Mettre à jour le tableau et d'autres vues si nécessaire
            ui->tableView_3->setModel(client.afficher());  // Actualiser la vue du client
            ui->modefierLabel->setPixmap(QPixmap(filePath));  // Afficher l'image dans le QLabel
            ui->modefierLabel->setScaledContents(true);  // Redimensionner l'image dans le QLabel
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la mise à jour de l'image.");
        }
    }
}
void MainWindow::setTableViewModel(QSqlQueryModel *model) {
    // Set the model for the table view
    ui->tableView->setModel(model);  // Ensure "tableView" is the correct widget name

    // Resize rows to fit the content (e.g., images, text)
    ui->tableView->resizeRowsToContents();  // Dynamically adjust row height based on content (e.g., images)

    // Set the item delegate for the "PHOTO" column (assuming it's column 6)
    ImageDelegate *imageDelegate = new ImageDelegate(this);
    ui->tableView->setItemDelegateForColumn(6, imageDelegate);  // Ensure the "PHOTO" column is the right one for displaying images

    // Optionally, set column width for better image display
    ui->tableView->setColumnWidth(6, 100);  // Width for the "PHOTO" column (column 6)
}

void MainWindow::on_pushButton_8_clicked()
{
     ui->stackedWidgetprincipale->setCurrentIndex(4);
     mettreAJourTableauFournisseurs();

}


void MainWindow::on_returnfournissurs_clicked()
{
    ui->stackedWidgetprincipale->setCurrentIndex(2);
}









void MainWindow::on_affichelefournissurs_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(0);
     mettreAJourTableauFournisseurs();
}


void MainWindow::on_ajoutunfournissursbout_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(1);
}


void MainWindow::on_ladurabilote_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(2);
}


void MainWindow::on_modificationfournissurs_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(3);
}


void MainWindow::on_arduino_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(4);
}


void MainWindow::on_affichelefournissurs_2_clicked()
{
     ui->stackedWidgetfournissurs->setCurrentIndex(0);
     mettreAJourTableauFournisseurs();
}


void MainWindow::on_ajoutunfournissurs_2_clicked()
{
     ui->stackedWidgetfournissurs->setCurrentIndex(1);
}


void MainWindow::on_ladurabilote_2_clicked()
{
     ui->stackedWidgetfournissurs->setCurrentIndex(2);
}


void MainWindow::on_modificationfournissurs_2_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(3);
}


void MainWindow::on_arduino_2_clicked()
{
     ui->stackedWidgetfournissurs->setCurrentIndex(4);

}


void MainWindow::on_affichelefournissurs_3_clicked()
{
     ui->stackedWidgetfournissurs->setCurrentIndex(0);
     mettreAJourTableauFournisseurs();
}


void MainWindow::on_ajoutunfournissurs_3_clicked()
{
     ui->stackedWidgetfournissurs->setCurrentIndex(1);
}


void MainWindow::on_ladurabilote_3_clicked()
{
     ui->stackedWidgetfournissurs->setCurrentIndex(2);
}


void MainWindow::on_modificationfournissurs_3_clicked()
{
     ui->stackedWidgetfournissurs->setCurrentIndex(3);
}


void MainWindow::on_arduino_fournissures_clicked()
{
     ui->stackedWidgetfournissurs->setCurrentIndex(4);
}


void MainWindow::on_affichelefournissurs_5_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(0);
     mettreAJourTableauFournisseurs();
}


void MainWindow::on_ajoutunfournissurs_5_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(1);
}


void MainWindow::on_ladurabilote_5_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(2);
}


void MainWindow::on_modificationfournissurs_4_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(3);
}


void MainWindow::on_arduino_fournissures_2_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(4);
}


void MainWindow::on_affichelefournissurs_4_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(0);
     mettreAJourTableauFournisseurs();
}


void MainWindow::on_ajoutunfournissurs_4_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(1);
}


void MainWindow::on_ladurabilote_4_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(2);
}


void MainWindow::on_modificationfour_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(3);
}


void MainWindow::on_arduino_3_clicked()
{
    ui->stackedWidgetfournissurs->setCurrentIndex(4);
}


void MainWindow::on_pushButton_ajouter_2_clicked()
{
    qDebug() << "Ajouter button clicked"; // Message de débogage

    // Retrieve values from UI fields
    int id = ui->lineEdit_ID_2->text().toInt();
    QString nom = ui->lineEdit_nom_2->text();
    QString telephone = ui->lineEdit_telephone_2->text();
    QString produitfournis = ui->lineEdit_produit_2->text();
    QString datecollaboration = ui->lineEdit_date_2->text();
    QString adresse = ui->lineEdit_adresse_2->text();
    float materiauxRecycles = ui->materiauxLineEdit_2->text().toFloat();
    float empreinteCarbone = ui->carboneLineEdit_2->text().toFloat();
    QString rfidId = ui->lineEdit_2_RFID->text();  // Get the RFID ID

    // Create a new fournisseur object
    fournisseur nouvF(id, nom, telephone, produitfournis, datecollaboration, adresse, materiauxRecycles, empreinteCarbone, rfidId);

    // Try to add the fournisseur
    bool test = nouvF.ajouter();

    if (test) {
        QMessageBox::information(this, tr("Succès"), tr("Le fournisseur a été ajouté avec succès."), QMessageBox::Ok);
        // Refresh the display in the QTableView
        ui->tableView_5->setModel(nouvF.afficher());
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("L'ajout du fournisseur a échoué."), QMessageBox::Cancel);
    }
}


void MainWindow::on_pushButton_supprimer_clicked()
{

}


void MainWindow::on_pushButton_supprimerfournissurs_clicked()
{
    qDebug() << "Supprimer button clicked"; // Message de débogage

    // Récupérer l'ID du fournisseur à partir du champ de saisie
    int id = ui->lineEdit_IDS->text().toInt();
    bool test = Etmp.supprimer(id);

    if (test) {
        QMessageBox::information(this, tr("Succès"), tr("Suppression effectuée."), QMessageBox::Ok);
        // Rafraîchir l'affichage dans le QTableView
        ui->tableView_5->setModel(Etmp.afficher());
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Échec de la suppression."), QMessageBox::Cancel);
    }
}


void MainWindow::on_rechercherfournissurs_clicked()
{
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

        ui->tableView_5->setModel(model);  // Affichage dans le tableau
    } else {
        QMessageBox::information(this, "Search Result", "Fournisseur with ID " + QString::number(id) + " does not exist.");

        // Optionnel : Vider ou réinitialiser le tableau en cas de non-trouvaille
        ui->tableView_5->setModel(nullptr);
    }
}


void MainWindow::on_pb_pdf_fournissurs_clicked()
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


void MainWindow::on_pushButton_trier_fournissurs_clicked()
{
    qDebug() << "Trier button clicked"; // Debug message

    // Sort the employees by ID
    bool ascending = true; // Set to false if you want to sort in descending order
    ui->tableView_5->setModel(Etmp.trierParID(ascending));
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


void MainWindow::on_pushButton_stats_clicked()
{
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








void MainWindow::on_modification_fournissurs_clicked()
{
    // Récupérer l'ID sélectionné dans le comboBox
    int idFournisseur = ui->comboBox_id_fournissurs->currentText().toInt();

    if (idFournisseur == 0) {  // Vérifier si un ID valide est sélectionné
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un fournisseur.");
        return;
    }

    // Récupérer les nouvelles données saisies par l'utilisateur
    QString nom = ui->lineEdit_nom_33->text();
    QString telephone = ui->lineEdit_telephone_33->text();
    QString produitfournis = ui->lineEdit_produit_33->text();
    QString datecollaboration = ui->lineEdit_date_33->text();
    QString adresse = ui->lineEdit_adresse_33->text();
    float materiauxRecycles = ui->materiauxLineEdit_33->text().toFloat();
    float empreinteCarbone = ui->carboneLineEdit_33->text().toFloat();
    QString rfidId = ui->lineEdit_2_RFID_33->text();

    // Créer un objet fournisseur et définir les nouvelles données
    fournisseur fournisseurToModify;
    fournisseurToModify.setNom(nom);
    fournisseurToModify.setTelephone(telephone);
    fournisseurToModify.setProduitfournis(produitfournis);
    fournisseurToModify.setDatecollaboration(datecollaboration);
    fournisseurToModify.setAdresse(adresse);
    fournisseurToModify.setMateriauxRecycles(materiauxRecycles);
    fournisseurToModify.setEmpreinteCarbone(empreinteCarbone);
    fournisseurToModify.setRfidId(rfidId);

    // Modifier le fournisseur dans la base de données
    if (fournisseurToModify.modifier(idFournisseur)) {
        QMessageBox::information(this, "Succès", "Fournisseur modifié avec succès.");
        mettreAJourTableauFournisseurs();  // Actualiser le tableau après modification
        chargerFournisseursDansComboBox();  // Actualiser le comboBox
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du fournisseur.");
    }
}

void MainWindow::chargerFournisseursDansComboBox() {
    QSqlQuery query;

    // Exécuter la requête pour récupérer les IDs des fournisseurs
    if (!query.exec("SELECT ID FROM FOURNISSEURS")) {
        qDebug() << "Erreur lors de la récupération des fournisseurs : " << query.lastError().text();
        return;
    }

    // Effacer les anciennes valeurs du comboBox
    ui->comboBox_id_fournissurs->clear();

    // Ajouter chaque ID au comboBox
    while (query.next()) {
        int idFournisseur = query.value(0).toInt();
        ui->comboBox_id_fournissurs->addItem(QString::number(idFournisseur));
    }
}


void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
    chargerFournisseursDansComboBox();  // Char

}

void MainWindow::mettreAJourTableauFournisseurs() {
    QSqlQueryModel *model = new QSqlQueryModel();

    // Requête SQL pour récupérer les données des fournisseurs
    model->setQuery("SELECT ID, NOM, TELEPHONE, PRODUIT_FOURNIS, DATE_COLLABORATION, ADRESSE, MATERIAUX_RECYCLES, EMPREINTE_CARBONE, RFID_ID FROM FOURNISSEURS");

    // Vérifier s'il y a des erreurs dans la requête SQL
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de l'affichage des fournisseurs : " << model->lastError().text();
        QMessageBox::critical(this, "Erreur", "Impossible de charger les données des fournisseurs.");
        return;
    }

    // Associer le modèle au QTableView
    ui->tableView_5->setModel(model);
    qDebug() << "Tableau des fournisseurs mis à jour avec succès.";
}

void MainWindow::on_recherrbouton_clicked()
{
     mettreAJourTableauFournisseurs();
}



void MainWindow::readSerialData() {
    if (arduino->getserial()->isReadable()) {
        QByteArray receivedData = arduino->read_from_arduino();  // Lire les données brutes

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
                query.prepare("SELECT NOM, ID FROM FOURNISSEURS WHERE RFID_ID = :rfid_id");
                query.bindValue(":rfid_id", rfidID);

                if (query.exec()) {
                    if (query.next()) {
                        QString fournisseurNom = query.value(0).toString();  // Récupérer le nom du fournisseur
                        QString fournisseurID = query.value(1).toString();  // Récupérer l'ID du fournisseur
                        qDebug() << "Nom du fournisseur trouvé :" << fournisseurNom;
                        qDebug() << "ID du fournisseur trouvé :" << fournisseurID;

                        // Mettre à jour le QLabel avec le nom et l'ID du fournisseur
                        ui->label_nom_four->setText(fournisseurNom);  // Afficher le nom dans le QLabel


                        // Mettre à jour le QLineEdit avec l'ID RFID
                        ui->lineEdit_FournisseurID_10->setText(rfidID);  // Afficher l'ID RFID dans le QLineEdit

                        // Envoyer le nom et l'ID du fournisseur à l'écran LCD
                        sendToArduino(fournisseurNom, fournisseurID);
                    } else {
                        qDebug() << "Aucun fournisseur trouvé pour le RFID_ID :" << rfidID;

                        // Si aucun fournisseur n'est trouvé, afficher un message d'erreur
                        ui->label_nom_four->setText("Fournisseur non trouvé");

                        ui->lineEdit_FournisseurID_10->setText(rfidID);
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


void MainWindow::afficherFournisseurParRFID(const QString &rfid_id) {
    QSqlQuery query;
    query.prepare("SELECT ID, NOM FROM FOURNISSEURS WHERE RFID_ID = :rfid_id");
    query.bindValue(":rfid_id", rfid_id);

    if (query.exec()) {
        if (query.next()) {
            // Récupérer les données
            int id = query.value("ID").toInt();
            QString nom = query.value("NOM").toString();

            // Envoi vers l'écran Arduino
            QString output = "ID: " + QString::number(id) + "; Nom: " + nom;
            arduino->write_to_arduino(output.toUtf8());  // Envoi des données formatées à Arduino
        } else {
            qDebug() << "Aucun fournisseur trouvé pour RFID:" << rfid_id;
        }
    } else {
        qDebug() << "Erreur SQL:" << query.lastError().text();
    }
}

void MainWindow::readFromArduino() {
    QByteArray data = serial->readAll();  // Lire les données du port série
    QString incomingData = QString(data).trimmed();  // Convertir les données en QString et les nettoyer
    rfidBuffer += incomingData;  // Ajouter les nouvelles données au tampon

    // Afficher le tampon actuel pour débogage
    qDebug() << "Tampon RFID actuel:" << rfidBuffer;

    // Vérifier si le tampon contient un RFID complet
    QStringList expectedRFIDs = {"AB0F3B", "C954E02A"};  // Liste des RFID attendus
    bool found = false;

    for (const QString &rfid : expectedRFIDs) {
        if (rfidBuffer.contains(rfid)) {
            // Si un RFID complet est trouvé, traiter l'ID
            rfidBuffer.clear();  // Vider le tampon après avoir trouvé un RFID complet
            ui->lineEdit_FournisseurID_10->setText(rfid);  // Afficher le RFID dans un champ Qt
            searchFournisseurByRFID(rfid);  // Rechercher le fournisseur par RFID
            qDebug() << "RFID complet trouvé:" << rfid;
            found = true;
            break;  // Quitter la boucle une fois un RFID trouvé
        }
    }

    if (!found) {
        qDebug() << "RFID incomplet, en attente de plus de données...";
    }
}

void MainWindow::searchFournisseurByRFID(const QString& rfid) {
    qDebug() << "Recherche fournisseur pour RFID:" << rfid;

    // Préparer la requête SQL pour rechercher le fournisseur par RFID
    QSqlQuery query;
    query.prepare("SELECT ID, NOM FROM FOURNISSEURS WHERE UPPER(RFID_ID) = UPPER(:rfid_id)");
    query.bindValue(":rfid_id", rfid);

    if (query.exec()) {
        if (query.next()) {
            // Récupérer les données du fournisseur
            QString fournisseurID = query.value("ID").toString();
            QString fournisseurNom = query.value("NOM").toString();

            // Afficher le nom et l'ID du fournisseur dans les champs Qt
            ui->lineEdit_FournisseurID_10->setText(fournisseurID);
            ui->label_nom_four->setText(fournisseurNom);

            // Envoyer les informations à l'Arduino
            sendToArduino(fournisseurID, fournisseurNom);  // Envoi à Arduino
        } else {
            qDebug() << "Aucun fournisseur trouvé pour RFID:" << rfid;
            ui->lineEdit_FournisseurID_10->clear();
            ui->label_nom_four->clear();
        }
    } else {
        qDebug() << "Erreur SQL:" << query.lastError().text();
    }
}
void MainWindow::setupArduino() {
    serial = new QSerialPort(this);
    serial->setPortName("COM3");  // Remplacez par le bon port
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {  // Ouvrir le port en lecture et écriture
        qDebug() << "Port série ouvert avec succès.";
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::readFromArduino);  // Connecter à la fonction de lecture
    } else {
        qDebug() << "Erreur d'ouverture du port série:" << serial->errorString();
    }
}
void MainWindow::sendToArduino(const QString &fournisseurID, const QString &fournisseurNom) {
    QString dataToSend = "Nom: " + fournisseurNom + "; ID: " + fournisseurID + "\n";
    if (serial && serial->isOpen()) {
        serial->write(dataToSend.toUtf8());
    }
}

void MainWindow::on_submitBtn_clicked()
{
    // Récupérer les valeurs des champs d'entrée
    QString id = ui->IDInput->text();               // ID : QLineEdit
    QString name = ui->nameInput->text();            // Nom : QLineEdit
    QString type = ui->typeInput->text();            // Type : QLineEdit
    int quantity = ui->quantityInput->value();      // Quantité : QSpinBox
    QString utility = ui->utilityInput->text();     // Utilité : QLineEdit

    // Créer une instance de Equipment (attention à la casse)
    Equipment equip(id, name, type, quantity, utility);

    // Ajouter dans la base de données
    QSqlDatabase db = QSqlDatabase::database();
    if (equip.ajouter(db)) {
        // Réinitialiser les champs d'entrée après l'ajout
        ui->IDInput->clear();
        ui->nameInput->clear();
        ui->typeInput->clear();
        ui->quantityInput->setValue(0); // Réinitialiser le SpinBox
        ui->utilityInput->clear();

        // Optionnel: afficher un message de confirmation
        QMessageBox::information(this, "Succès", "Équipement ajouté avec succès!");
    } else {
        // Afficher une erreur si l'ajout échoue
        QMessageBox::critical(this, "Erreur", "L'ajout de l'équipement a échoué.");
    }
}


void MainWindow::on_pushButton_9_clicked()
{
     ui->stackedWidgetprincipale->setCurrentIndex(5);
}


void MainWindow::findEquipmentToUpdate() {
    QString id = ui->updateInput->text().trimmed();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID d'équipement valide.");
        return;
    }

    // Obtenir la base de données active
    QSqlDatabase db = QSqlDatabase::database();

    // Rechercher l'équipement par son ID
    QSqlQuery query(db);
    query.prepare("SELECT id, name, type, quantity, utility FROM EQUIPMENTS WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la recherche : " + query.lastError().text());
        return;
    }

    if (!query.next()) { // Si aucun équipement trouvé
        QMessageBox::information(this, "Non trouvé", "Équipement non trouvé. Vérifiez l'ID et réessayez.");
        return;
    }

    // Récupérer les détails de l'équipement
    QString foundId = query.value("id").toString();
    QString foundName = query.value("name").toString();
    QString foundType = query.value("type").toString();
    int foundQuantity = query.value("quantity").toInt();
    QString foundUtility = query.value("utility").toString();

    // Remplir les champs avec les détails de l'équipement trouvé
    ui->upIDInput->setText(foundId);
    ui->upNameInput->setText(foundName);
    ui->upTypeInput->setText(foundType);
    ui->upQuantityInput->setValue(foundQuantity);
    ui->upUtilityInput->setText(foundUtility);

    // Rendre les champs visibles
    ui->upIDInput->setVisible(true);
    ui->upNameInput->setVisible(true);
    ui->upTypeInput->setVisible(true);
    ui->upQuantityInput->setVisible(true);
    ui->upUtilityInput->setVisible(true);
    ui->updateBtn->setVisible(true);

    // Afficher un message de succès
    QMessageBox::information(this, "Équipement trouvé", "Équipement trouvé. Modifiez les détails et cliquez sur Mettre à jour.");
}
void MainWindow::updateEquipment() {
    // Récupérer les valeurs des champs de saisie
    QString id = ui->upIDInput->text().trimmed();
    QString name = ui->upNameInput->text().trimmed();
    QString type = ui->upTypeInput->text().trimmed();
    int quantity = ui->upQuantityInput->value();
    QString utility = ui->upUtilityInput->text().trimmed();

    // Vérification des champs vides
    if (id.isEmpty() || name.isEmpty() || type.isEmpty() || utility.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez remplir tous les champs avant de mettre à jour.");
        return;
    }

    // Créer un objet Equipment
    Equipment equipment(id, name, type, quantity, utility);

    // Obtenir la base de données active
    QSqlDatabase db = QSqlDatabase::database();

    // Appeler la méthode mettreAJour pour mettre à jour l'équipement
    if (equipment.mettreAJour(db)) {
        // Afficher un message de succès
        QMessageBox::information(this, "Succès", "L'équipement a été mis à jour avec succès !");

        // Masquer les champs et le bouton après la mise à jour
        ui->upIDInput->setVisible(false);
        ui->upNameInput->setVisible(false);
        ui->upTypeInput->setVisible(false);
        ui->upQuantityInput->setVisible(false);
        ui->upUtilityInput->setVisible(false);
        ui->updateBtn->setVisible(false);
    } else {
        // Afficher un message d'échec
        QMessageBox::critical(this, "Échec", "La mise à jour a échoué. Vérifiez les logs pour plus de détails.");
    }
}
void MainWindow::handleDeleteBtnClick() {
    // Récupérer l'ID de l'équipement à supprimer
    QString equipmentId = ui->deleteInput->text().trimmed();

    // Vérifier si le champ est vide
    if (equipmentId.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez entrer un ID d'équipement à supprimer.");
        return;
    }

    // Créer un objet Equipment
    Equipment equipment("", "", "", 0, "");

    // Obtenir la base de données active
    QSqlDatabase db = QSqlDatabase::database();

    // Supprimer l'équipement
    if (equipment.supprimer(db, equipmentId)) {
        // Afficher un message de succès
        QMessageBox::information(this, "Succès", "L'équipement a été supprimé avec succès.");
        ui->deleteInput->clear();
    } else {
        // Afficher un message d'échec
        QMessageBox::critical(this, "Échec", "Équipement introuvable avec cet ID. Vérifiez l'ID et réessayez.");
    }
}
void MainWindow::handleSearchBtnClick() {
    ui->searchTable->setColumnCount(5);
    ui->searchTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});
    // Récupérer l'ID de l'équipement à rechercher
    QString equipmentId = ui->searchInput->text().trimmed();

    // Vérifier si le champ est vide
    if (equipmentId.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez entrer un ID d'équipement pour la recherche.");
        return;
    }

    // Obtenir la base de données active
    QSqlDatabase db = QSqlDatabase::database();

    // Appeler la fonction rechercher pour trouver l'équipement par ID
    Equipment equipment = Equipment::rechercher(db, equipmentId);

    // Si l'équipement est trouvé
    if (!equipment.getId().isEmpty()) {
        // Effacer les lignes précédentes dans le tableau
        ui->searchTable->setRowCount(0);  // Réinitialiser le tableau

        // Ajouter les détails de l'équipement trouvé dans le tableau (une seule ligne)
        ui->searchTable->setRowCount(1);  // Une seule ligne pour le résultat

        // Remplir le tableau avec les détails de l'équipement trouvé
        ui->searchTable->setItem(0, 0, new QTableWidgetItem(equipment.getId()));
        ui->searchTable->setItem(0, 1, new QTableWidgetItem(equipment.getName()));
        ui->searchTable->setItem(0, 2, new QTableWidgetItem(equipment.getType()));
        ui->searchTable->setItem(0, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
        ui->searchTable->setItem(0, 4, new QTableWidgetItem(equipment.getUtility()));

        // Afficher un message de succès
        QMessageBox::information(this, "Succès", "Équipement trouvé et affiché.");
    } else {
        // Si l'équipement n'est pas trouvé, afficher un message d'échec
        ui->searchTable->setRowCount(0);  // Réinitialiser le tableau
        QMessageBox::warning(this, "Échec", "Aucun équipement trouvé avec cet ID.");
    }
}
void MainWindow::handleSearchByNameBtnClick() {
    ui->searchByNameTable->setColumnCount(5);
    ui->searchByNameTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});
    QString searchQuery = ui->searchByNameInput->text().trimmed();  // Obtenir le texte saisi par l'utilisateur

    if (searchQuery.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Veuillez entrer un nom pour la recherche.");
        return;
    }

    // Obtenir la base de données active
    QSqlDatabase db = QSqlDatabase::database();

    // Appeler la fonction rechercherParNom pour trouver les équipements par nom
    QList<Equipment> results = Equipment::rechercherParNom(db, searchQuery);

    // Effacer le tableau avant d'ajouter les nouveaux résultats
    ui->searchByNameTable->setRowCount(0);

    if (!results.isEmpty()) {
        // Ajouter chaque équipement dans le tableau
        for (const Equipment &equipment : results) {
            int row = ui->searchByNameTable->rowCount();
            ui->searchByNameTable->insertRow(row);
            ui->searchByNameTable->setItem(row, 0, new QTableWidgetItem(equipment.getId()));
            ui->searchByNameTable->setItem(row, 1, new QTableWidgetItem(equipment.getName()));
            ui->searchByNameTable->setItem(row, 2, new QTableWidgetItem(equipment.getType()));
            ui->searchByNameTable->setItem(row, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
            ui->searchByNameTable->setItem(row, 4, new QTableWidgetItem(equipment.getUtility()));
        }

        // Message de succès
        QMessageBox::information(this, "Succès", QString::number(results.size()) + " équipement(s) trouvé(s).");
    } else {
        // Aucun résultat trouvé
        QMessageBox::warning(this, "Aucun résultat", "Aucun équipement trouvé avec le nom '" + searchQuery + "'.");
    }
}

void MainWindow::sortEquipmentsAsc() {
    sortEquipments(true);
}

void MainWindow::sortEquipmentsDesc() {
    sortEquipments(false);
}

void MainWindow::sortEquipments(bool ascending) {
    ui->sortTable->setColumnCount(5);
    ui->sortTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});
    // Obtenir la base de données active
    QSqlDatabase db = QSqlDatabase::database();

    // Obtenir la liste des équipements triés
    QList<Equipment> equipments = Equipment::trier(db, ascending);

    // Vérifier si des équipements ont été trouvés
    if (equipments.isEmpty()) {
        QMessageBox::warning(this, "Aucun équipement", "Aucun équipement trouvé pour le tri.");
        return;
    }

    // Effacer le tableau avant d'ajouter les équipements triés
    ui->sortTable->setRowCount(0);

    // Ajouter chaque équipement trié dans le tableau
    for (int i = 0; i < equipments.size(); ++i) {
        const Equipment &equipment = equipments[i];
        ui->sortTable->insertRow(i);

        ui->sortTable->setItem(i, 0, new QTableWidgetItem(equipment.getId()));
        ui->sortTable->setItem(i, 1, new QTableWidgetItem(equipment.getName()));
        ui->sortTable->setItem(i, 2, new QTableWidgetItem(equipment.getType()));
        ui->sortTable->setItem(i, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
        ui->sortTable->setItem(i, 4, new QTableWidgetItem(equipment.getUtility()));
    }

    // Mettre à jour le label avec l'ordre de tri actuel
    QString sortOrder = ascending ? "CROISSANT" : "DECROISSANT";
    ui->sortLabel->setText(QString("(%1 TOTAL DES EQUIPEMENTS TRIES %2)")
                               .arg(equipments.size())
                               .arg(sortOrder));

    // Afficher un message de succès
    QMessageBox::information(this, "Tri réussi", QString::number(equipments.size()) + " équipements triés avec succès.");
}
void MainWindow::exportEquipmentsAsCSV() {
    // Ouvrir la boîte de dialogue pour choisir le fichier à enregistrer
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save CSV"), "", tr("CSV Files (*.csv)"));
    if (fileName.isEmpty()) {
        return;
    }

    // Créer un objet QFile pour le fichier CSV
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open the file for writing.");
        return;
    }

    // Créer un QTextStream pour écrire dans le fichier
    QTextStream out(&file);

    // Écrire les en-têtes du fichier CSV
    out << "ID,Name,Type,Quantity,Utility\n";

    // Obtenir la liste des équipements à partir de la base de données
    QSqlDatabase db = QSqlDatabase::database();
    QList<Equipment> equipmentList = Equipment::afficher(db);

    // Vérifier si la liste d'équipements est vide
    if (equipmentList.isEmpty()) {
        QMessageBox::information(this, "No Equipment", "No equipment data found to export.");
        return;
    }

    // Écrire les données des équipements dans le fichier CSV
    for (const Equipment &equipment : equipmentList) {
        out << equipment.getId() << ","
            << equipment.getName() << ","
            << equipment.getType() << ","
            << equipment.getQuantity() << ","
            << equipment.getUtility() << "\n"; // Données de la ligne
    }

    // Fermer le fichier
    file.close();

    // Afficher un message de succès
    QMessageBox::information(this, "Export Successful", "Equipment list exported as CSV.");
}

void MainWindow::goToRetrievePage() {
    int pageIndex = ui->stackedWidgetEquip->indexOf(ui->retrievePage);
    ui->stackedWidgetEquip->setCurrentIndex(pageIndex);

    // Populate the table with data
    populateEquipmentsTable();
}

void MainWindow::goToUpdatePage() {
    int pageIndex = ui->stackedWidgetEquip->indexOf(ui->updatePage);
    ui->stackedWidgetEquip->setCurrentIndex(pageIndex);

    ui->upIDInput->setVisible(false);
    ui->upNameInput->setVisible(false);
    ui->upTypeInput->setVisible(false);
    ui->upQuantityInput->setVisible(false);
    ui->upUtilityInput->setVisible(false);
    ui->updateBtn->setVisible(false);
}

void MainWindow::goToAddPage() {
    int pageIndex = ui->stackedWidgetEquip->indexOf(ui->addPage);
    ui->stackedWidgetEquip->setCurrentIndex(pageIndex);
}

void MainWindow::goToDeletePage() {
    int pageIndex = ui->stackedWidgetEquip->indexOf(ui->deletePage);
    ui->stackedWidgetEquip->setCurrentIndex(pageIndex);
}

void MainWindow::goToSearchPage() {
    int pageIndex = ui->stackedWidgetEquip->indexOf(ui->searchPage);
    ui->stackedWidgetEquip->setCurrentIndex(pageIndex);

    ui->searchTable->setColumnCount(5);
    ui->searchTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});
}

void MainWindow::goToSearchByNamePage() {
    int pageIndex = ui->stackedWidgetEquip->indexOf(ui->searchByNamePage);
    ui->stackedWidgetEquip->setCurrentIndex(pageIndex);

    ui->searchByNameTable->setColumnCount(5);
    ui->searchByNameTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});
}

void MainWindow::goToSortPage() {
    int pageIndex = ui->stackedWidgetEquip->indexOf(ui->sortPage);
    ui->stackedWidgetEquip->setCurrentIndex(pageIndex);

    ui->sortTable->setColumnCount(5);
    ui->sortTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});

    sortEquipmentsAsc();
}

void MainWindow::goToExportPage() {
    int pageIndex = ui->stackedWidgetEquip->indexOf(ui->exportPage);
    ui->stackedWidgetEquip->setCurrentIndex(pageIndex);
}

void MainWindow::goToStatPage() {
    renderStatisticsPage();
    int pageIndex = ui->stackedWidgetEquip->indexOf(ui->statPage);
    ui->stackedWidgetEquip->setCurrentIndex(pageIndex);
}
void MainWindow::populateEquipmentsTable() {
    // Effacer le tableau avant de le remplir
    ui->equipmentsTable->setRowCount(0);

    // Récupérer toutes les données des équipements
        QSqlDatabase db = QSqlDatabase::database();
    QList<Equipment> equipmentList = Equipment::afficher(db);

    // Définir les en-têtes des colonnes
    ui->equipmentsTable->setColumnCount(5);
    ui->equipmentsTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});

    // Remplir le tableau avec les données
    for (int i = 0; i < equipmentList.size(); ++i) {
        const Equipment &equipment = equipmentList[i];

        // Ajouter une nouvelle ligne
        ui->equipmentsTable->insertRow(i);

        // Remplir les colonnes avec les données
        ui->equipmentsTable->setItem(i, 0, new QTableWidgetItem(equipment.getId()));
        ui->equipmentsTable->setItem(i, 1, new QTableWidgetItem(equipment.getName()));
        ui->equipmentsTable->setItem(i, 2, new QTableWidgetItem(equipment.getType()));
        ui->equipmentsTable->setItem(i, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
        ui->equipmentsTable->setItem(i, 4, new QTableWidgetItem(equipment.getUtility()));
    }

    // Mettre à jour le label avec le nombre total d'équipements
    ui->equipmentCountLabel->setText(QString("TOUTES LES EQUIPEMENTS: (%1 TOTAL)").arg(equipmentList.size()));
}

void MainWindow::renderStatisticsPage() {
        QSqlDatabase db = QSqlDatabase::database();

    // Obtenir les statistiques de base
    int totalEquipments = Equipment::getTotalEquipmentCount(db);
    int aboveThreshold = Equipment::getEquipmentCountAboveThreshold(5, db);
    int belowThreshold = totalEquipments - aboveThreshold;

    double abovePercentage = (totalEquipments > 0) ? (aboveThreshold * 100.0) / totalEquipments : 0.0;
    double belowPercentage = 100.0 - abovePercentage;

    // Mettre à jour les labels avec les statistiques
    ui->statLabel->setText(QString("STATISTIQUES DES EQUIPMENTS: %1 EQUIEPMENTS EN TOTAL").arg(totalEquipments));
    ui->aboveLabel->setText(QString("%1 EQUIPMENTS ABOVE 5 IN QUANTITY: %2%")
                                .arg(aboveThreshold)
                                .arg(QString::number(abovePercentage, 'f', 2)));
    ui->belowLabel->setText(QString("%1 EQUIPMENTS BELOW 5 IN QUANTITY: %2%")
                                .arg(belowThreshold)
                                .arg(QString::number(belowPercentage, 'f', 2)));

    // Configurer les tableaux
    ui->aboveTable->setColumnCount(5);
    ui->aboveTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});
    ui->belowTable->setColumnCount(5);
    ui->belowTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});

    // Remplir le tableau "aboveTable" avec les équipements au-dessus du seuil
    ui->aboveTable->setRowCount(0);
    QList<Equipment> aboveList = Equipment::getEquipmentsAboveThreshold(5, db);
    for (int i = 0; i < aboveList.size(); ++i) {
        const Equipment &equipment = aboveList[i];
        ui->aboveTable->insertRow(i);
        ui->aboveTable->setItem(i, 0, new QTableWidgetItem(equipment.getId()));
        ui->aboveTable->setItem(i, 1, new QTableWidgetItem(equipment.getName()));
        ui->aboveTable->setItem(i, 2, new QTableWidgetItem(equipment.getType()));
        ui->aboveTable->setItem(i, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
        ui->aboveTable->setItem(i, 4, new QTableWidgetItem(equipment.getUtility()));
    }

    // Remplir le tableau "belowTable" avec les équipements en dessous du seuil
    ui->belowTable->setRowCount(0);
    QList<Equipment> belowList = Equipment::getEquipmentsBelowThreshold(5, db);
    for (int i = 0; i < belowList.size(); ++i) {
        const Equipment &equipment = belowList[i];
        ui->belowTable->insertRow(i);
        ui->belowTable->setItem(i, 0, new QTableWidgetItem(equipment.getId()));
        ui->belowTable->setItem(i, 1, new QTableWidgetItem(equipment.getName()));
        ui->belowTable->setItem(i, 2, new QTableWidgetItem(equipment.getType()));
        ui->belowTable->setItem(i, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
        ui->belowTable->setItem(i, 4, new QTableWidgetItem(equipment.getUtility()));
    }
}

void MainWindow::on_returnclients_2_clicked()
{

        ui->stackedWidgetprincipale->setCurrentIndex(2);

}

