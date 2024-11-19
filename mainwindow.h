#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>

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

private:
    Ui::MainWindow *ui;
    QSqlQueryModel *model;

};

#endif // MAINWINDOW_H
