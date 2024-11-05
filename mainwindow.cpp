#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    QSqlQuery query(connection->getDatabase());
    query.prepare("INSERT INTO equipments (id, name, type, quantity, utility) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(id);
    query.addBindValue(name);
    query.addBindValue(type);
    query.addBindValue(quantity);
    query.addBindValue(utility);

    if (!query.exec()) {
        qDebug() << "Insert Error:" << query.lastError().text(); // Log error message
    } else {
        qDebug() << "Data inserted successfully! ID:" << id << ", Name:" << name << ", Type:" << type << ", Quantity:" << quantity << ", Utility:" << utility;
        ui->IDInput->clear();
        ui->nameInput->clear();
        ui->typeInput->clear();
        ui->quantityInput->clear();
        ui->utilityInput->clear();
        ui->statusBar->showMessage("Data saved to the database.", 6000);
    }
}

void MainWindow::handleDeleteBtnClick() {
    QString equipmentId = ui->deleteInput->text();

    if (equipmentId.isEmpty()) {
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("Please enter an Equipment ID to delete.", 6000);
        return;
    }

    QSqlQuery query(connection->getDatabase());
    query.prepare("DELETE FROM equipments WHERE id = ?");
    query.addBindValue(equipmentId);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            ui->statusBar->setStyleSheet("color: green;");
            ui->statusBar->showMessage("Equipment deleted successfully.", 6000);
            ui->deleteInput->clear();
        } else {
            ui->statusBar->setStyleSheet("color: red;");
            ui->statusBar->showMessage("No equipment found with the provided ID.", 6000);
        }
    } else {
        qDebug() << "Delete Error:" << query.lastError().text();
        ui->statusBar->setStyleSheet("color: red;");
        ui->statusBar->showMessage("Error deleting equipment from the database.", 6000);
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
