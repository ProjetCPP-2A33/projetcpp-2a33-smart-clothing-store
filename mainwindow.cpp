#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipment.h"
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->submitBtn, &QPushButton::clicked, this, &MainWindow::handleSubmitBtnClick);
    connect(ui->retrievePageBtn, &QPushButton::clicked, this, &MainWindow::goToRetrievePage);
    connect(ui->updatePageBtn, &QPushButton::clicked, this, &MainWindow::goToUpdatePage);
    connect(ui->deletePageBtn, &QPushButton::clicked, this, &MainWindow::goToDeletePage);
    connect(ui->addPageBtn, &QPushButton::clicked, this, &MainWindow::goToAddPage);
    connect(ui->searchPageBtn, &QPushButton::clicked, this, &MainWindow::goToSearchPage);
    connect(ui->sortPageBtn, &QPushButton::clicked, this, &MainWindow::goToSortPage);
    connect(ui->exportPageBtn, &QPushButton::clicked, this, &MainWindow::goToExportPage);
    connect(ui->searchByNamePageBtn, &QPushButton::clicked, this, &MainWindow::goToSearchByNamePage);
    connect(ui->statPageBtn, &QPushButton::clicked, this, &MainWindow::goToStatPage);
    connect(ui->deleteBtn, &QPushButton::clicked, this, &MainWindow::handleDeleteBtnClick);
    connect(ui->searchBtn, &QPushButton::clicked, this, &MainWindow::handleSearchBtnClick);
    connect(ui->searchByNameBtn, &QPushButton::clicked, this, &MainWindow::handleSearchByNameBtnClick);
    connect(ui->ascBtn, &QPushButton::clicked, this, &MainWindow::sortEquipmentsAsc);
    connect(ui->descBtn, &QPushButton::clicked, this, &MainWindow::sortEquipmentsDesc);
    connect(ui->updateFindBtn, &QPushButton::clicked, this, &MainWindow::findEquipmentToUpdate);
    connect(ui->updateBtn, &QPushButton::clicked, this, &MainWindow::updateEquipment);
    connect(ui->exportBtn, &QPushButton::clicked, this, &MainWindow::exportEquipmentsAsCSV);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDatabaseConnection(Connection *conn) {
    connection = conn;
}

void MainWindow::handleSubmitBtnClick() {
    // Retrieve input values
    QString id = ui->IDInput->text();
    QString name = ui->nameInput->text();
    QString type = ui->typeInput->text();
    int quantity = ui->quantityInput->value();
    QString utility = ui->utilityInput->text();

    // Check if any input is empty
    if (id.isEmpty() || name.isEmpty() || type.isEmpty() || utility.isEmpty()) {
        // Set error message for empty fields
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("All fields must be filled in!", 5000);
        return;
    }

    // Create an Equipment object with the input values
    Equipment equipment(id, name, type, quantity, utility);

    // Try to add the equipment to the database
    if (equipment.ajouter(connection->getDatabase())) {
        // Success message
        ui->statusBar->setStyleSheet("color: green;");
        ui->statusBar->showMessage("Data saved to the database.", 5000);

        // Clear the inputs after successful submission
        ui->IDInput->clear();
        ui->nameInput->clear();
        ui->typeInput->clear();
        ui->quantityInput->clear();
        ui->utilityInput->clear();
    } else {
        // Failure message
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("Failed to add equipment.", 5000);
    }
}

void MainWindow::handleDeleteBtnClick() {
    QString equipmentId = ui->deleteInput->text();

    if (equipmentId.isEmpty()) {
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("Please enter an Equipment ID to delete.", 6000);
        return;
    }

    Equipment equipment("", "", "", 0, "");
    if (equipment.supprimer(connection->getDatabase(), equipmentId)) {
        ui->statusBar->showMessage("Equipment deleted successfully.", 5000);
        ui->statusBar->setStyleSheet("color: green;");
        ui->deleteInput->clear();
    } else {
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("Equipment with this ID was not found.", 5000);
    }
}

void MainWindow::goToRetrievePage() {
    int pageIndex = ui->stackedWidget->indexOf(ui->retrievePage);
    ui->stackedWidget->setCurrentIndex(pageIndex);

    // Populate the table with data
    populateEquipmentsTable();
}

void MainWindow::goToUpdatePage() {
    int pageIndex = ui->stackedWidget->indexOf(ui->updatePage);
    ui->stackedWidget->setCurrentIndex(pageIndex);

    ui->upIDInput->setVisible(false);
    ui->upNameInput->setVisible(false);
    ui->upTypeInput->setVisible(false);
    ui->upQuantityInput->setVisible(false);
    ui->upUtilityInput->setVisible(false);
    ui->updateBtn->setVisible(false);
}

void MainWindow::goToAddPage() {
    int pageIndex = ui->stackedWidget->indexOf(ui->addPage);
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::goToDeletePage() {
    int pageIndex = ui->stackedWidget->indexOf(ui->deletePage);
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::goToSearchPage() {
    int pageIndex = ui->stackedWidget->indexOf(ui->searchPage);
    ui->stackedWidget->setCurrentIndex(pageIndex);

    ui->searchTable->setColumnCount(5);
    ui->searchTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});
}

void MainWindow::goToSearchByNamePage() {
    int pageIndex = ui->stackedWidget->indexOf(ui->searchByNamePage);
    ui->stackedWidget->setCurrentIndex(pageIndex);

    ui->searchByNameTable->setColumnCount(5);
    ui->searchByNameTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});
}

void MainWindow::goToSortPage() {
    int pageIndex = ui->stackedWidget->indexOf(ui->sortPage);
    ui->stackedWidget->setCurrentIndex(pageIndex);

    ui->sortTable->setColumnCount(5);
    ui->sortTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});

    sortEquipmentsAsc();
}

void MainWindow::goToExportPage() {
    int pageIndex = ui->stackedWidget->indexOf(ui->exportPage);
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::goToStatPage() {
    renderStatisticsPage();
    int pageIndex = ui->stackedWidget->indexOf(ui->statPage);
    ui->stackedWidget->setCurrentIndex(pageIndex);
}

void MainWindow::populateEquipmentsTable() {
    // Clear the table before populating
    ui->equipmentsTable->setRowCount(0);

    // Retrieve all equipment data
    QList<Equipment> equipmentList = Equipment::afficher(connection->getDatabase());

    // Set column headers
    ui->equipmentsTable->setColumnCount(5);
    ui->equipmentsTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});

    // Populate the table with data
    for (int i = 0; i < equipmentList.size(); ++i) {
        const Equipment &equipment = equipmentList[i];

        // Add a new row
        ui->equipmentsTable->insertRow(i);

        // Populate the row with data
        ui->equipmentsTable->setItem(i, 0, new QTableWidgetItem(equipment.getId()));
        ui->equipmentsTable->setItem(i, 1, new QTableWidgetItem(equipment.getName()));
        ui->equipmentsTable->setItem(i, 2, new QTableWidgetItem(equipment.getType()));
        ui->equipmentsTable->setItem(i, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
        ui->equipmentsTable->setItem(i, 4, new QTableWidgetItem(equipment.getUtility()));

        int rowCount = ui->equipmentsTable->rowCount();  // Get the number of rows in the table

        // Update the label with the total count
        QString labelText = QString("ALL EQUIPMENTS: (%1 TOTAL)").arg(rowCount);
        ui->equipmentCountLabel->setText(labelText);  // Assuming your label has this name
    }
}

void MainWindow::handleSearchBtnClick() {
    // Get the equipment ID from the input field
    QString equipmentId = ui->searchInput->text();

    // Check if the input is empty
    if (equipmentId.isEmpty()) {
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("Please enter an Equipment ID to search.", 5000);
        return;
    }

    // Call the findById function to search the equipment by ID
    Equipment equipment = Equipment::rechercher(connection->getDatabase(), equipmentId);

    // If the equipment is found
    if (!equipment.getId().isEmpty()) {
        // Clear previous rows (if any) in the table
        ui->searchTable->setRowCount(0);  // Reset the table

        // Add the found equipment details to the table (in a single row)
        ui->searchTable->setRowCount(1);  // Only one row for the result

        // Populate the table with the found equipment details
        ui->searchTable->setItem(0, 0, new QTableWidgetItem(equipment.getId()));
        ui->searchTable->setItem(0, 1, new QTableWidgetItem(equipment.getName()));
        ui->searchTable->setItem(0, 2, new QTableWidgetItem(equipment.getType()));
        ui->searchTable->setItem(0, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
        ui->searchTable->setItem(0, 4, new QTableWidgetItem(equipment.getUtility()));

        // Show a success message in the status bar
        ui->statusBar->setStyleSheet("color: green;");
        ui->statusBar->showMessage("Equipment found and displayed.", 5000);
    } else {
        // If equipment is not found, show a failure message in the status bar
        ui->searchTable->setRowCount(0);
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("No equipment found with the given ID.", 5000);
    }
}

void MainWindow::handleSearchByNameBtnClick() {
    QString searchQuery = ui->searchByNameInput->text();  // Get the text entered by the user

    if (searchQuery.isEmpty()) {
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("Please enter a name to search.", 5000);
        return;
    }

    QList<Equipment> results = Equipment::rechercherParNom(connection->getDatabase(), searchQuery);

    // Clear the table before inserting new results
    ui->searchByNameTable->setRowCount(0);

    if (!results.isEmpty()) {
        // Add each equipment to the table
        for (const Equipment &equipment : results) {
            int row = ui->searchByNameTable->rowCount();
            ui->searchByNameTable->insertRow(row);
            ui->searchByNameTable->setItem(row, 0, new QTableWidgetItem(equipment.getId()));
            ui->searchByNameTable->setItem(row, 1, new QTableWidgetItem(equipment.getName()));
            ui->searchByNameTable->setItem(row, 2, new QTableWidgetItem(equipment.getType()));
            ui->searchByNameTable->setItem(row, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
            ui->searchByNameTable->setItem(row, 4, new QTableWidgetItem(equipment.getUtility()));
        }

        // Success message
        ui->statusBar->setStyleSheet("color: green;");
        ui->statusBar->showMessage(QString::number(results.size()) + " equipment(s) found.", 6000);
    } else {
        // No results found
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("No equipment found with the name '" + searchQuery + "'.", 5000);
    }
}

void MainWindow::sortEquipments(bool ascending) {
    // Get sorted equipment list from the database
    QList<Equipment> equipments = Equipment::trier(connection->getDatabase(), ascending);

    // Clear the table and populate it with sorted equipments
    ui->sortTable->setRowCount(0);
    for (int i = 0; i < equipments.size(); ++i) {
        const Equipment &equipment = equipments[i];
        ui->sortTable->insertRow(i);

        ui->sortTable->setItem(i, 0, new QTableWidgetItem(equipment.getId()));
        ui->sortTable->setItem(i, 1, new QTableWidgetItem(equipment.getName()));
        ui->sortTable->setItem(i, 2, new QTableWidgetItem(equipment.getType()));
        ui->sortTable->setItem(i, 3, new QTableWidgetItem(QString::number(equipment.getQuantity())));
        ui->sortTable->setItem(i, 4, new QTableWidgetItem(equipment.getUtility()));
    }

    // Update sortLabel with the current sort order
    QString sortOrder = ascending ? "ASCENDING" : "DESCENDING";
    ui->sortLabel->setText(QString("(%1 TOTAL EQUIPMENTS SORTED %2)")
                               .arg(equipments.size())
                               .arg(sortOrder));
}

void MainWindow::sortEquipmentsAsc() {
    sortEquipments(true);
}

void MainWindow::sortEquipmentsDesc() {
    sortEquipments(false);
}

void MainWindow::findEquipmentToUpdate() {
    QString id = ui->updateInput->text().trimmed();

    if (id.isEmpty()) {
        ui->statusBar->showMessage("Please enter a valid equipment ID.", 3000);
        return;
    }

    Equipment foundEquipment = Equipment::rechercher(connection->getDatabase(), id);

    if (foundEquipment.getId().isEmpty()) { // Equipment not found
        ui->statusBar->showMessage("Equipment not found. Check the ID and try again.", 3000);
        ui->statusBar->setStyleSheet("color: red;");
        return;
    }

    // Populate inputs with the found equipment details
    ui->upIDInput->setText(foundEquipment.getId());
    ui->upNameInput->setText(foundEquipment.getName());
    ui->upTypeInput->setText(foundEquipment.getType());
    ui->upQuantityInput->setValue(foundEquipment.getQuantity());
    ui->upUtilityInput->setText(foundEquipment.getUtility());

    ui->upIDInput->setVisible(true);
    ui->upNameInput->setVisible(true);
    ui->upTypeInput->setVisible(true);
    ui->upQuantityInput->setVisible(true);
    ui->upUtilityInput->setVisible(true);
    ui->updateBtn->setVisible(true);

    ui->statusBar->showMessage("Equipment found. Edit the details and click Update.", 3000);
    ui->statusBar->setStyleSheet("color: green;");
}

void MainWindow::updateEquipment() {
    QString id = ui->upIDInput->text().trimmed();
    QString name = ui->upNameInput->text().trimmed();
    QString type = ui->upTypeInput->text().trimmed();
    int quantity = ui->upQuantityInput->value();
    QString utility = ui->upUtilityInput->text().trimmed();

    if (id.isEmpty() || name.isEmpty() || type.isEmpty() || utility.isEmpty()) {
        ui->statusBar->showMessage("Please fill in all fields before updating.", 3000);
        ui->statusBar->setStyleSheet("color: red;");
        return;
    }

    Equipment equipment(id, name, type, quantity, utility);
    if (equipment.mettreAJour(connection->getDatabase())) {
        ui->statusBar->showMessage("Equipment updated successfully!", 3000);
        ui->statusBar->setStyleSheet("color: green;");

        ui->upIDInput->setVisible(false);
        ui->upNameInput->setVisible(false);
        ui->upTypeInput->setVisible(false);
        ui->upQuantityInput->setVisible(false);
        ui->upUtilityInput->setVisible(false);
        ui->updateBtn->setVisible(false);
    } else {
        ui->statusBar->showMessage("Failed to update equipment. Check the logs for details.", 3000);
        ui->statusBar->setStyleSheet("color: red;");
    }
}

void MainWindow::exportEquipmentsAsCSV() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save CSV"), "", tr("CSV Files (*.csv)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open the file for writing!";
        return;
    }

    QTextStream out(&file);

    out << "ID,Name,Type,Quantity,Utility\n";

    QList<Equipment> equipmentList = Equipment::afficher(connection->getDatabase());

    for (const Equipment& equipment : equipmentList) {
        out << equipment.getId() << ","
            << equipment.getName() << ","
            << equipment.getType() << ","
            << equipment.getQuantity() << ","
            << equipment.getUtility() << "\n"; // Row data
    }

    file.close();

    ui->statusBar->setStyleSheet("color: green;");
    ui->statusBar->showMessage("Equipment list exported as CSV.");
}

void MainWindow::renderStatisticsPage() {
    QSqlDatabase db = connection->getDatabase();

    int totalEquipments = Equipment::getTotalEquipmentCount(db);
    int aboveThreshold = Equipment::getEquipmentCountAboveThreshold(5, db);
    int belowThreshold = totalEquipments - aboveThreshold;

    double abovePercentage = (aboveThreshold * 100.0) / totalEquipments;
    double belowPercentage = 100.0 - abovePercentage;

    ui->statLabel->setText(QString("EQUIPMENT STATISTICS: %1 EQUIPMENT IN TOTAL").arg(totalEquipments));

    ui->aboveLabel->setText(QString("%1 EQUIPMENTS ABOVE 5 IN QUANTITY: %2%")
                                .arg(aboveThreshold)
                                .arg(QString::number(abovePercentage, 'f', 2)));
    ui->belowLabel->setText(QString("%1 EQUIPMENTS BELOW 5 IN QUANTITY: %2%")
                                .arg(belowThreshold)
                                .arg(QString::number(belowPercentage, 'f', 2)));

    ui->aboveTable->setColumnCount(5);
    ui->aboveTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});
    ui->belowTable->setColumnCount(5);
    ui->belowTable->setHorizontalHeaderLabels({"ID", "Name", "Type", "Quantity", "Utility"});

    ui->aboveTable->setRowCount(0);
    QList<Equipment> aboveList = Equipment::getEquipmentsAboveThreshold(5, db);
    for (int i = 0; i < aboveList.size(); ++i) {
        ui->aboveTable->insertRow(i);
        ui->aboveTable->setItem(i, 0, new QTableWidgetItem(aboveList[i].getId()));
        ui->aboveTable->setItem(i, 1, new QTableWidgetItem(aboveList[i].getName()));
        ui->aboveTable->setItem(i, 2, new QTableWidgetItem(aboveList[i].getType()));
        ui->aboveTable->setItem(i, 3, new QTableWidgetItem(QString::number(aboveList[i].getQuantity())));
        ui->aboveTable->setItem(i, 4, new QTableWidgetItem(aboveList[i].getUtility()));
    }

    ui->belowTable->setRowCount(0);
    QList<Equipment> belowList = Equipment::getEquipmentsBelowThreshold(5, db);
    for (int i = 0; i < belowList.size(); ++i) {
        ui->belowTable->insertRow(i);
        ui->belowTable->setItem(i, 0, new QTableWidgetItem(belowList[i].getId()));
        ui->belowTable->setItem(i, 1, new QTableWidgetItem(belowList[i].getName()));
        ui->belowTable->setItem(i, 2, new QTableWidgetItem(belowList[i].getType()));
        ui->belowTable->setItem(i, 3, new QTableWidgetItem(QString::number(belowList[i].getQuantity())));
        ui->belowTable->setItem(i, 4, new QTableWidgetItem(belowList[i].getUtility()));
    }
}












