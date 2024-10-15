#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
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
    void openClientsWindow(); // Déclaration de la méthode pour ouvrir la fenêtre Clients
};

#endif // MAINWINDOW_H
