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
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    employe p;
    ui->emptable->setModel(p.afficherEmploye());
    ui->emptable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setPixmap(QPixmap(":/images/bg.jpeg").scaled(this->size(), Qt::KeepAspectRatioByExpanding));
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(0, 0, this->width(), this->height());

    backgroundLabel->lower();
    backgroundLabel->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    loadHistoriqueFile();

    this->setWindowTitle("Chic Admin");
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
    employe p;

    QString nom = ui->ajouternom->text();
    QString prenom = ui->ajouterprenom->text();
    QString mail = ui->ajoutermail->text();
    QString mot_de_passe = ui->ajoutermotdepasse->text();
    int num_tel = ui->ajouternumtel->text().toInt();
    QString adresse = ui->ajouteradresse->text();
    QString genre = ui->combogenre_2->currentText();

    p.setNom(nom);
    p.setPrenom(prenom);
    p.setMail(mail);
    p.setMotDePasse(mot_de_passe);
    p.setNumTel(num_tel);
    p.setAdresse(adresse);
    p.setGenre(genre); // Set genre

    if (p.ajouterEmploye(p)) {
        QMessageBox::information(this, "Succès", "Employe ajouté avec succès!");
        ui->ajouternom->clear();
        ui->ajouterprenom->clear();
        ui->ajoutermail->clear();
        ui->ajoutermotdepasse->clear();
        ui->ajouternumtel->clear();
        ui->ajouteradresse->clear();
        ui->combogenre_2->setCurrentIndex(0); // Reset combo box to first item

        ui->emptable->setModel(p.afficherEmploye());
        historique("Ajout", "success", "Employe Ajouté " + nom);
        qDebug() << "Employe ajouté avec succès!";
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employe.");
        qDebug() << "Échec de l'ajout dans la base";
    }
}

void MainWindow::on_pushButton_clicked()
{

        // Change the current page in the stacked widget
        ui->stackedWidgetemploye->setCurrentWidget(ui->pagestatistiques);

        // Vérifiez si un layout existe déjà pour éviter de le recréer à chaque fois
        QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(ui->pagestatistiques->layout());
        if (!layout) {
            layout = new QVBoxLayout(ui->pagestatistiques);
            ui->pagestatistiques->setLayout(layout);
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
        query.exec("SELECT COUNT(*) FROM employe GROUP BY GENRE");
        int malecount = query.next() ? query.value(0).toInt() : 0;

        query.exec("SELECT COUNT(*) FROM employe GROUP BY GENRE ");
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
    int id_emp = ui->idsupprimer->text().toInt();

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

        ui->idsupprimer->clear();
        ui->emptable->setModel(p.afficherEmploye());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidgetemploye->setCurrentWidget(ui->page);

    QString filePath = QCoreApplication::applicationDirPath() + "/historique.txt";
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur","fichier historique vide");
        return;
    }

    QTextStream in(&file);
    QString historiqueContent = in.readAll();
    file.close();

    ui->textHistorique->setPlainText(historiqueContent);
}

void MainWindow::on_bouttonrecherchetableau_clicked()
{

}


void MainWindow::on_pushButton_3_clicked()
{
    employe e ;
    QSqlQueryModel *model = e.trieparnom();
    if(model){
        ui->emptable->setModel(model);

    }


}


void MainWindow::on_bouttonafficheremloyes_clicked()
{
    employe e;
    ui->stackedWidgetemploye->setCurrentWidget(ui->pageafficheremployes);
    ui->emptable->setModel(e.afficherEmploye());
}


void MainWindow::on_bouttonafficherpagesupprimer_clicked()
{
    ui->stackedWidgetemploye->setCurrentWidget(ui->pagesupprimer);
}


void MainWindow::on_bouttonafficherajoutemploye_clicked()
{
    ui->stackedWidgetemploye->setCurrentWidget(ui->pageajouteremploye);
}


void MainWindow::on_bouttonrecherche_clicked()
{

        employe e;
    QString recherche = ui->inputrecherche->text();

    QSqlQueryModel* model = e.rechercheparnom(recherche);

    if (model) {
        ui->emptable->setModel(model);
    } else {
        qDebug() << "pas de model";
    }
}


void MainWindow::on_buttontriparnom_clicked()
{
    employe e;
    QSqlQueryModel* model = e.trieparnom();
    ui->emptable->setModel(model);

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
    ui->stackedWidgetemploye->setCurrentWidget(ui->pagemodifieremloye);

}


void MainWindow::on_bouttonconfirmermodif_clicked()
{
    employe e;
    int id_emp = ui->idemployemodif->text().toInt();
    QString nom = ui->ajouternom_3->text();
    QString prenom = ui->ajouterprenom_3->text();
    QString mail = ui->ajoutermail_3->text();
    QString mot_de_passe = ui->ajoutermotdepasse_3->text();
    int num_tel = ui->ajouternumtel_3->text().toInt();
    QString adresse = ui->ajouteradresse_3->text();
    QString genre = ui->combogenre->currentText(); // Get genre from combo box

    if (e.modifierEmploye(id_emp, nom, prenom, mail, mot_de_passe, num_tel, adresse, genre)) {
        qDebug() << "Employe modifié";
        QMessageBox::information(this, "Succès", "Employe modifié");
        historique("Modification", "success", "Employe Modifié " + QString::number(id_emp));

        ui->ajouternom_3->clear();
        ui->ajouterprenom_3->clear();
        ui->ajoutermail_3->clear();
        ui->ajoutermotdepasse_3->clear();
        ui->ajouternumtel_3->clear();
        ui->ajouteradresse_3->clear();
        ui->combogenre->setCurrentIndex(0); // Reset combo box to first item

        ui->emptable->setModel(e.afficherEmploye());
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification.");
    }
}

void MainWindow::on_bouttonconfirmeridmodif_clicked()
{
    // Retrieve the entered ID
    int id_emp = ui->idemployemodif->text().toInt();

    // Validate that the ID is not empty or invalid
    if (id_emp <= 0) {
        QMessageBox::warning(this, "Invalid ID", "Please enter a valid employee ID.");
        return;
    }

    // Query the database for the employee with the given ID
    QSqlQuery query;
    query.prepare("SELECT nom, prenom, mail, mot_de_passe, num_tel, adresse FROM employe WHERE id_emp = :id_emp");
    query.bindValue(":id_emp", id_emp);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to execute the query.");
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

        ui->ajouternom_3->setText(nom);
        ui->ajouterprenom_3->setText(prenom);
        ui->ajoutermail_3->setText(mail);
        ui->ajoutermotdepasse_3->setText(mot_de_passe);
        ui->ajouternumtel_3->setText(QString::number(num_tel));
        ui->ajouteradresse_3->setText(adresse);

        QMessageBox::information(this, "Employee Found", "Employee details loaded successfully.");
    } else {
        QMessageBox::warning(this, "Employee Not Found", "No employee found with the given ID.");
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

    ui->textHistorique->setPlainText(content);
}



