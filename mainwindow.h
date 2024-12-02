#ifndef MAINWINDOW_H
#define MAINWINDOW_H
<<<<<<< HEAD
#include "fournisseur.h"
#include "connection.h"
#include <QMainWindow>
#include <QMainWindow>
#include <QSqlQueryModel>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QSqlQuery>
#include <QSqlError>
#include <QtCharts/QPieSlice>
#include <QLayout>
#include <QLayoutItem>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QRandomGenerator>
#include <QSqlQueryModel>  // Ajoutez cette ligne pour utiliser QSqlQueryModel
#include <QSqlQuery>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QSqlRecord>
#include "arduino.h"
#include <QTimer>


namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
=======

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
>>>>>>> 6970123e40de339b0298ce361cc13ba1279501a0
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
<<<<<<< HEAD
    // void envoyerDonneesArduino(const QString &rfidID);
    ~MainWindow();
   // void sendDataToArduino();
    void sendNameToLCD(const QString &nom);

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pb_pdf_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_trier_clicked();
    void on_calculerDurabilite_clicked();
    float calculerDurabilite(float materiauxRecycles, float empreinteCarbone);
    bool chargerFournisseurParId(int id);  // Récupère les données du fournisseur par son ID
    void on_pushButton_stats_clicked();
    void searchAndDisplayRFID();
    void checkRFID();
    //void readRFIDFromArduino();
    //void rechercherFournisseurParRFID(const QString &rfidID);
    void on_rechercher_idrf_clicked();
   void readSerialData();

      //void setupRFIDReading();

private:

    Ui::MainWindow *ui;
    fournisseur Etmp;
    Arduino arduino;
    QTimer *rfidTimer;
     QString rfidID;

=======
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton *buttonArticle;
    QPushButton *buttonClients;
    QPushButton *buttonCommandes;
    QPushButton *buttonEmployes;
    QPushButton *buttonFournisseurs;
    QPushButton *buttonEquipements;
    QPushButton *buttonQuitter;

public slots:
    void openClientsWindow(); // Slot to open the Clients window
    void closeApplication(); // Slot to handle Quitter button
>>>>>>> 6970123e40de339b0298ce361cc13ba1279501a0
};

#endif // MAINWINDOW_H
