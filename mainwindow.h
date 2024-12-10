#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"product.h"
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
   //houni t7ot les fonctions kima bouton ajout ki t3ml slot




    void on_pushButton_ajouter_clicked();

    void on_pushButton_rechparid_clicked();

    void on_pushButton_recheparnom_clicked();

    void on_pushButton_modifier_clicked();

    void on_pushButton_trier_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_statistique_clicked();

    void on_pushButton_exporterpdf_clicked();

    void on_pushButton_recommenknn_clicked();



    void on_tableView_recommendations_clicked(const QModelIndex &index);

    void on_tableView_clicked(const QModelIndex &index);
    void displayCharts_clientByGender();

    void on_back_button_clicked();
    void readSerial();
    void readFromArduino22();
    void readData();

private:
    Ui::MainWindow *ui;
    product nouveauProduit ;
    QSerialPort serial;
      void setupSerial();
      int checkUnavailableProducts();
      ////////////////arduino/////////////////
            QSerialPort *arduino;
            QByteArray dataToSend = "2";
            QByteArray lastDataSent = "";


};
#endif // MAINWINDOW_H
