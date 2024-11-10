#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commande.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>


Commande commande;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_commande->setModel(commande.afficher());
    populateStatutComboBox();
    displayCommandeStat();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateStatutComboBox() {
    ui->comboBox_satut->addItem("Completee ");
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
        Commande commande(date_creation, statut, quantity, montant_total);

        // Appeler la méthode ajouter() pour insérer les données dans la base de données
        bool success = commande.ajouter();

        // Afficher un message en fonction du résultat de l'opération
        if (success) {
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

void MainWindow::on_modfi_cd_clicked()
{
    // Retrieve values from the user interface
       int id = ui->idCommande->text().toInt();  // Assuming there's an ID field to identify the record
       QDate date_creation = ui->dateEdit_date->date();
       QString statut = ui->comboBox_satut->currentText();
       int quantite = ui->lineEdit_quantite->text().toInt();

       int montant_total = ui->lineEdit_montant->text().toInt();

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
       Commande commande(id, date_creation, statut, quantite, montant_total);

       // Call the modifier() method to update the record in the database
       bool success = commande.modifier(id);

       // Display a message based on the result of the operation
       if (success) {
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

void MainWindow::on_lineEdit_textChanged(QString text)
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

void MainWindow::on_pdf_cd_clicked()
{
generatePDF("");
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

