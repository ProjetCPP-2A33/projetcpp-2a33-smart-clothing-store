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
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    employe e;
    Arduino arduino;
    ui->emptable_2->setModel(e.afficherEmploye());
    ui->emptable_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    ui->stackedWidgetprincipale->setCurrentWidget(ui->pageconnection);

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


}void MainWindow::Read_Data()
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

