#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ClientsWindow;
}

class ClientsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientsWindow(QWidget *parent = nullptr);
    ~ClientsWindow();

private slots:
    void showAjoute();
    void showSupprime();
    void showModifier();
    void showParametres();
    void handleRetour();
    void handleButtonClick(QPushButton* clickedButton);

private:
    Ui::ClientsWindow *ui;
    QPushButton* activeButton = nullptr;  // Membre pour garder le bouton actif

};

#endif // CLIENTSWINDOW_H
