#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipment.h"

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
    connect(ui->searchByNamePageBtn, &QPushButton::clicked, this, &MainWindow::goToSearchByNamePage);
    connect(ui->deleteBtn, &QPushButton::clicked, this, &MainWindow::handleDeleteBtnClick);
    connect(ui->searchBtn, &QPushButton::clicked, this, &MainWindow::handleSearchBtnClick);
    connect(ui->searchByNameBtn, &QPushButton::clicked, this, &MainWindow::handleSearchByNameBtnClick);
    connect(ui->ascBtn, &QPushButton::clicked, this, &MainWindow::sortEquipmentsAsc);
    connect(ui->descBtn, &QPushButton::clicked, this, &MainWindow::sortEquipmentsDesc);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDatabaseConnection(Connection *conn) {
    connection = conn;
}

void MainWindow::handleSubmitBtnClick() {
    QString id = ui->IDInput->text();
    QString name = ui->nameInput->text();
    QString type = ui->typeInput->text();
    int quantity = ui->quantityInput->text().toInt();
    QString utility = ui->utilityInput->text();

    Equipment equipment(id, name, type, quantity, utility);

    if (equipment.ajouter(connection->getDatabase())) {
        ui->statusBar->showMessage("Data saved to the database.", 5000);
        ui->IDInput->clear();
        ui->nameInput->clear();
        ui->typeInput->clear();
        ui->quantityInput->clear();
        ui->utilityInput->clear();
    } else {
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("Failed to add equipment.");
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
        ui->statusBar->showMessage("Equipment with this ID was not found.");
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
        ui->statusBar->showMessage("Please enter a name to search.");
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
        ui->statusBar->showMessage(QString::number(results.size()) + " equipment(s) found.");
    } else {
        // No results found
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("No equipment found with the name '" + searchQuery + "'.");
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

