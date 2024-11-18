#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "connection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setDatabaseConnection(Connection *conn);

private slots:
    void handleSubmitBtnClick();
    void handleDeleteBtnClick();
    void handleSearchBtnClick();
    void handleSearchByNameBtnClick();
    void goToAddPage();
    void goToRetrievePage();
    void goToUpdatePage();
    void goToDeletePage();
    void goToSearchPage();
    void goToSearchByNamePage();
    void goToSortPage();
    void sortEquipments(bool ascending);
    void sortEquipmentsAsc();
    void sortEquipmentsDesc();

private:
    Ui::MainWindow *ui;
    Connection *connection;

    void populateEquipmentsTable();
};
#endif // MAINWINDOW_H
