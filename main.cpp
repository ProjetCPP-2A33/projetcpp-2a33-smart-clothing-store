#include "mainwindow.h"
#include "connection.h"
#include "arduino.h"
#include "produit.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Connect to the database
    Connection dbConnection;
    dbConnection.createconnect();

    MainWindow w;
    w.show();
    w.setDatabaseConnection(&dbConnection);

    // Initialize Arduino communication
    initializeArduino();

    // Check products availability
    QSqlDatabase db = dbConnection.getDatabase();
    Produit produit(&db);

    int unavailableCount = produit.countUnavailableProducts();
    if (unavailableCount == 0) {
        QMessageBox::warning(&w, "Products Unavailable",
                             QString("There are %1 products unavailable!").arg(unavailableCount));
        sendBuzzCommand(); // Buzz if there are unavailable products
    } else {
        QMessageBox::information(&w, "All Products Available",
                                 "All products are available.");
    }

    return a.exec();
}
