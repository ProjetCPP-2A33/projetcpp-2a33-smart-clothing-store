#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QTableView>
#include <QGraphicsScene>

#include <QMainWindow>
  // Ajouter cette ligne
  // Ajouter si vous utilisez QGraphicsView
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QColor>
<<<<<<< HEAD
=======
#include <QVBoxLayout>


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)



namespace Ui {
    class ClientsWindow;
}

class ClientsWindow : public QWidget {
    Q_OBJECT

public:

    explicit ClientsWindow(QWidget *parent = nullptr);
    ~ClientsWindow();
     void setTableViewModel(QSqlQueryModel *model);
     void displayStatistics();
     void afficherStatistiques();
<<<<<<< HEAD
private:
    Ui::ClientsWindow *ui;
    QPushButton *activeButton = nullptr;  // Déclarer activeButton ici
=======


   void envoyerWhatsApp(const QString &numeroClient);
private:
    Ui::ClientsWindow *ui;
    QPushButton *activeButton = nullptr;  // Déclarer activeButton ici
  QString currentImagePath;
   QString selectedImagePath;
>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)

    QGraphicsScene *scene;
        void setupButtonSound();  // Fonction pour configurer le son pour tous les boutons
    void handleButtonClick(QPushButton* clickedButton);  // Déclarer handleButtonClick

private slots:
<<<<<<< HEAD
=======

>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
    void handleRetour();
    // Déclarer handleRetour
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_11_clicked();


    void updateIdField();
    void on_pushButton_12_clicked();
    void refreshAllTablesAndViews();

    void exporterPDF();


   void on_trierParNom_clicked();


    void on_recherche_textChanged(const QString &text);
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_27_clicked();
<<<<<<< HEAD
   void on_clientsButton_clicked();
   void displaySexeStatistics();
   void updateSexeCycle(int maleCount, int femaleCount);



  void on_pushButton_clients_clicked();

=======


   void updateSexeCycle(int maleCount, int femaleCount);

  void setLightMode();
  void setNightMode();
  void on_pushButton_clients_clicked();

  void on_lightButton_clicked();
  void on_nightButton_clicked();


  void on_normal_clicked();


  void on_notification_sms_clicked();



  void onNotificationSent();
 void addImageToTableView();
  void on_numtel_cursorPositionChanged(int arg1, int arg2);


  void on_ajoute_image_clicked();
  void on_mofeder_image_clicked();




  void rechercheParPath(const QString &imagePath);

void searchClientByImagePath(const QString& imagePath);


 void afficherClients1();

void rechercherClientParImage(const QString &imagePath);


void on_recherch_image_clicked();

>>>>>>> 6c5f7e3 (Ajout des fonctionnalités de gestion des clients)
};


#endif // CLIENTSWINDOW_H
