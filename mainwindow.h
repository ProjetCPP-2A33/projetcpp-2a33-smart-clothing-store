#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_ajouter_cd_clicked();

    void on_modfi_cd_clicked();

    void on_tableView_commande_doubleClicked(const QModelIndex &index);

    void on_supp_cd_clicked();

     void on_lineEdit_textChanged( QString text);

     void on_dateEdit_recherche_dateChanged(const QDate &date);

     void on_tri_cd_clicked();

     void on_pdf_cd_clicked();

private:
    Ui::MainWindow *ui;
    void populateStatutComboBox() ;
    void generatePDF( QString filePath);
    void displayCommandeStat();
};
#endif // MAINWINDOW_H
