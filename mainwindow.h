#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QDebug>
#include "arduino.h"  // Include the Arduino class header

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

    void on_bouttonajouter_clicked();


    void on_pushButton_clicked();

    void on_button_supprimer_clicked();

    void on_pushButton_2_clicked();

    void on_bouttonrecherchetableau_clicked();

    void on_pushButton_3_clicked();

    void on_bouttonafficheremloyes_clicked();

    void on_bouttonafficherpagesupprimer_clicked();

    void on_bouttonafficherajoutemploye_clicked();
    void resizeEvent(QResizeEvent *event);
    void on_bouttonrecherche_clicked();

    void on_buttontriparnom_clicked();

    void on_bouttonexportpdf_clicked();

    void historique(const QString &typeevenement, const QString &nomproduit, const QString &extrainfo);
    void loadHistoriqueFile();

    void on_bouttonafficherpagemodifieremploye_clicked();

    void on_bouttonconfirmermodif_clicked();

    void on_bouttonconfirmeridmodif_clicked();

    void on_bouttonformlogin_clicked();

    void on_bouttonlogin_clicked();

    void on_bouttonaffichergestionemp_clicked();

    void on_bouttonconnection_clicked();

    void on_bouttonafficheremloyes_2_clicked();

    void on_bouttonafficherpagemodifieremploye_2_clicked();

    void on_bouttonafficherajoutemploye_2_clicked();

    void on_bouttonafficherpagesupprimer_2_clicked();

    void on_bouttonajouter_2_clicked();

    void on_bouttonconfirmeridmodif_2_clicked();

    void on_button_supprimer_2_clicked();

    void on_bouttonconfirmeidmodif_clicked();

    void onDataReceived();  // Ensure this is declared only once

    void on_bouttonreaddata_clicked();
    void Read_Data();

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    Arduino a;  // Arduino object pointer
    QSerialPort* COMPORT;
    QString Data_From_SerialPort;
    bool IS_Data_Recevied = false;

};

#endif // MAINWINDOW_H
