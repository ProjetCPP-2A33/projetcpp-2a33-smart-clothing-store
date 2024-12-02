#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
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

};

#endif // MAINWINDOW_H
