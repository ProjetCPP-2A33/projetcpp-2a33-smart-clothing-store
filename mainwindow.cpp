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
    connect(ui->deleteBtn, &QPushButton::clicked, this, &MainWindow::handleDeleteBtnClick);

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
