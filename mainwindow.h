#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QDebug>
#include "arduino.h"  // Include the Arduino class header
#include <QGraphicsScene>
#include <QGraphicsPathItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void afficherStatistiques();
    void setTableViewModel(QSqlQueryModel *model);
    void displayStatistics();

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

    void on_pushButton_4_clicked();



    void on_modif_cd_clicked();

    void on_supp_cd_clicked();

    void on_pdf_cd_clicked();

    void on_tri_cd_clicked();

    void on_ajouter_cd_clicked();

    void on_tableView_commande_doubleClicked(const QModelIndex &index);





    void on_lineEdit_textChanged(  QString text);

    void on_dateEdit_recherche_dateChanged(const QDate &date);

    void on_calendarWidget_cd_selectionChanged();

    void on_back_clicked();

    void on_pushButton_5_clicked();

    void on_returnclients_clicked();

    void on_afficheclient_clicked();

    void on_ajouteclients_clicked();

    void on_modeferclients_clicked();

    void on_supprimelesclients_clicked();

    void on_parametreclients_clicked();

    void on_afficheclients2_clicked();

    void on_ajouteclients2_clicked();


    void on_modeferclinets2_clicked();

    void on_supprimeclients2_clicked();

    void on_parametreclients_2_clicked();

    void on_afficheclients3_clicked();

    void on_ajouteclients3_clicked();

    void on_moddeferclients3_clicked();

    void on_supprimeclients3_clicked();

    void on_parametreclients3_clicked();

    void on_afficheclients4_clicked();

    void on_ajouteclients4_clicked();

    void on_modeferclients4_clicked();

    void on_supprimeclients4_clicked();

    void on_parametreclients4_clicked();



    void on_afficheclients4_2_clicked();

    void on_ajjouteclinets4_clicked();

    void on_modeferclients4_2_clicked();

    void on_supprimeclients4_2_clicked();

    void on_parametre4_clicked();
    void updateSexeCycle(int maleCount, int femaleCount);

    void on_recherche_textChanged(const QString &text);
    void on_trierParNom_clicked();

    void on_ajouteunclients_clicked();

    void on_notification_sms_clicked();
    void envoyerWhatsApp(const QString &numeroClient);
    void on_modefieruclients_clicked();
    void onNotificationSent();
    void on_supprimeunclients_clicked();
    void exporterPDF();
    void setLightMode();
    void setNightMode();

    void on_lightButton_clicked();

    void on_nightButton_clicked();

    void on_normal_clicked();

    void on_recherch_image_clicked();
    void rechercherClientParImage(const QString &imagePath);

    void on_ajoute_image_clicked();
    void updateIdField();
    void updateStatistics();
    void on_mofeder_image_clicked();
    void on_updateStatisticsButton_clicked();


private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;
    Arduino a;  // Arduino object pointer
    QSerialPort* COMPORT;
    QString Data_From_SerialPort;
    bool IS_Data_Recevied = false;
   // QPushButton *activeButton = nullptr;  // Déclarer activeButton ici
    QString currentImagePath;
    QString selectedImagePath;


    void populateStatutComboBox() ;
    void generatePDF( QString filePath);
    void displayCommandeStat();
    void sendOrderConfirmationSMS();
    void populateClientComboBox();
    void sendSMS(const QString& to, const QString& message);
    void highlightOrderDates();
    void refreshAllTablesAndViews();
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
