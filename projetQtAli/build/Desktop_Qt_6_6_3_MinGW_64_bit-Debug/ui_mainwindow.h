/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QStackedWidget *stackedWidgetprincipale;
    QWidget *pageemp;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_8;
    QPushButton *bouttonafficheremloyes_2;
    QPushButton *bouttonafficherajoutemploye_2;
    QPushButton *bouttonafficherpagemodifieremploye_2;
    QPushButton *bouttonafficherpagesupprimer_2;
    QPushButton *pushButton_7;
    QStackedWidget *stackedWidgetemploye;
    QWidget *pageafficheremployes_2;
    QGridLayout *gridLayout_4;
    QTableView *emptable_2;
    QFrame *frame_9;
    QLineEdit *inputrecherche_2;
    QPushButton *bouttonrecherche_2;
    QPushButton *buttontriparnom_2;
    QWidget *pagesupprimer_2;
    QPushButton *button_supprimer_2;
    QLineEdit *idsupprimer_2;
    QLabel *label_22;
    QWidget *page_2;
    QLabel *label_41;
    QTextEdit *receiveddata;
    QWidget *pageajouteremploye_2;
    QPushButton *bouttonajouter_2;
    QFrame *frame_10;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QFrame *frame_11;
    QVBoxLayout *verticalLayout_10;
    QLineEdit *ajouternom_2;
    QLineEdit *ajouterprenom_2;
    QLineEdit *ajoutermail_2;
    QLineEdit *ajoutermotdepasse_2;
    QComboBox *combogenre_3;
    QLineEdit *ajouternumtel_2;
    QLineEdit *ajouteradresse_2;
    QWidget *pagemodifieremloye_2;
    QFrame *frame_12;
    QVBoxLayout *verticalLayout_11;
    QLineEdit *ajouternom_4;
    QLineEdit *ajouterprenom_4;
    QLineEdit *ajoutermail_4;
    QComboBox *combogenre_4;
    QLineEdit *ajoutermotdepasse_4;
    QLineEdit *ajouternumtel_4;
    QLineEdit *ajouteradresse_4;
    QPushButton *bouttonconfirmermodif_2;
    QFrame *frame_13;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QLineEdit *idemployemodif_2;
    QPushButton *bouttonconfirmeidmodif;
    QLabel *label_35;
    QWidget *page_4;
    QGridLayout *gridLayout_5;
    QTextEdit *textHistorique_2;
    QWidget *pagestatistiques_2;
    QLabel *label_40;
    QPushButton *bouttonexportpdf;
    QPushButton *bouttonformlogin;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *pageconnection;
    QPushButton *bouttonconnection;
    QFrame *frame_15;
    QVBoxLayout *verticalLayout_14;
    QLineEdit *inputloginform_2;
    QLineEdit *inputloginmotdepasse_2;
    QFrame *frame_14;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_38;
    QWidget *pagehomepage;
    QFrame *frame_16;
    QVBoxLayout *verticalLayout_15;
    QPushButton *bouttonaffichergestionemp;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QLabel *label_39;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1167, 743);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        stackedWidgetprincipale = new QStackedWidget(centralwidget);
        stackedWidgetprincipale->setObjectName("stackedWidgetprincipale");
        stackedWidgetprincipale->setStyleSheet(QString::fromUtf8("background-image:none;"));
        pageemp = new QWidget();
        pageemp->setObjectName("pageemp");
        pageemp->setStyleSheet(QString::fromUtf8("background-image:none;"));
        frame_3 = new QFrame(pageemp);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(30, 110, 251, 421));
        frame_3->setStyleSheet(QString::fromUtf8("#frame_3 {\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"QPushButton {\n"
"    background: white;\n"
"    border: none;\n"
"color:black;\n"
"}"));
        frame_3->setFrameShape(QFrame::Shape::StyledPanel);
        frame_3->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(frame_3);
        verticalLayout_8->setObjectName("verticalLayout_8");
        bouttonafficheremloyes_2 = new QPushButton(frame_3);
        bouttonafficheremloyes_2->setObjectName("bouttonafficheremloyes_2");
        bouttonafficheremloyes_2->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        bouttonafficheremloyes_2->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/headhunting.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouttonafficheremloyes_2->setIcon(icon);

        verticalLayout_8->addWidget(bouttonafficheremloyes_2);

        bouttonafficherajoutemploye_2 = new QPushButton(frame_3);
        bouttonafficherajoutemploye_2->setObjectName("bouttonafficherajoutemploye_2");
        bouttonafficherajoutemploye_2->setMinimumSize(QSize(0, 50));
        bouttonafficherajoutemploye_2->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/add-user.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouttonafficherajoutemploye_2->setIcon(icon1);

        verticalLayout_8->addWidget(bouttonafficherajoutemploye_2);

        bouttonafficherpagemodifieremploye_2 = new QPushButton(frame_3);
        bouttonafficherpagemodifieremploye_2->setObjectName("bouttonafficherpagemodifieremploye_2");
        bouttonafficherpagemodifieremploye_2->setMinimumSize(QSize(0, 50));
        bouttonafficherpagemodifieremploye_2->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/edit-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouttonafficherpagemodifieremploye_2->setIcon(icon2);

        verticalLayout_8->addWidget(bouttonafficherpagemodifieremploye_2);

        bouttonafficherpagesupprimer_2 = new QPushButton(frame_3);
        bouttonafficherpagesupprimer_2->setObjectName("bouttonafficherpagesupprimer_2");
        bouttonafficherpagesupprimer_2->setMinimumSize(QSize(0, 50));
        bouttonafficherpagesupprimer_2->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouttonafficherpagesupprimer_2->setIcon(icon3);

        verticalLayout_8->addWidget(bouttonafficherpagesupprimer_2);

        pushButton_7 = new QPushButton(frame_3);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setMinimumSize(QSize(0, 50));
        pushButton_7->setFont(font);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon4);

        verticalLayout_8->addWidget(pushButton_7);

        stackedWidgetemploye = new QStackedWidget(pageemp);
        stackedWidgetemploye->setObjectName("stackedWidgetemploye");
        stackedWidgetemploye->setGeometry(QRect(380, 130, 771, 471));
        stackedWidgetemploye->setStyleSheet(QString::fromUtf8("\n"
"    background: rgba(68,153,156,255);\n"
"    border: 1px solid lightgray;\n"
"color : black;\n"
"\n"
""));
        pageafficheremployes_2 = new QWidget();
        pageafficheremployes_2->setObjectName("pageafficheremployes_2");
        gridLayout_4 = new QGridLayout(pageafficheremployes_2);
        gridLayout_4->setObjectName("gridLayout_4");
        emptable_2 = new QTableView(pageafficheremployes_2);
        emptable_2->setObjectName("emptable_2");
        emptable_2->setStyleSheet(QString::fromUtf8("background-color:white;\n"
"color:black;"));
        emptable_2->verticalHeader()->setVisible(false);

        gridLayout_4->addWidget(emptable_2, 1, 0, 1, 1);

        frame_9 = new QFrame(pageafficheremployes_2);
        frame_9->setObjectName("frame_9");
        frame_9->setMinimumSize(QSize(0, 50));
        frame_9->setFrameShape(QFrame::Shape::StyledPanel);
        frame_9->setFrameShadow(QFrame::Shadow::Raised);
        inputrecherche_2 = new QLineEdit(frame_9);
        inputrecherche_2->setObjectName("inputrecherche_2");
        inputrecherche_2->setGeometry(QRect(50, 10, 281, 28));
        bouttonrecherche_2 = new QPushButton(frame_9);
        bouttonrecherche_2->setObjectName("bouttonrecherche_2");
        bouttonrecherche_2->setGeometry(QRect(360, 10, 91, 29));
        bouttonrecherche_2->setStyleSheet(QString::fromUtf8("QPushButton::hover{\n"
"background-color:rgb(110, 255, 134);\n"
"}\n"
"QPushButton::pressed{\n"
"background-color:rgb(39, 255, 64);\n"
"}"));
        buttontriparnom_2 = new QPushButton(frame_9);
        buttontriparnom_2->setObjectName("buttontriparnom_2");
        buttontriparnom_2->setGeometry(QRect(470, 10, 121, 29));
        buttontriparnom_2->setStyleSheet(QString::fromUtf8("QPushButton::hover{\n"
"background-color:rgb(110, 255, 134);\n"
"}\n"
"QPushButton::pressed{\n"
"background-color:rgb(39, 255, 64);\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/sorting.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttontriparnom_2->setIcon(icon5);

        gridLayout_4->addWidget(frame_9, 0, 0, 1, 1);

        stackedWidgetemploye->addWidget(pageafficheremployes_2);
        pagesupprimer_2 = new QWidget();
        pagesupprimer_2->setObjectName("pagesupprimer_2");
        button_supprimer_2 = new QPushButton(pagesupprimer_2);
        button_supprimer_2->setObjectName("button_supprimer_2");
        button_supprimer_2->setGeometry(QRect(250, 220, 161, 51));
        idsupprimer_2 = new QLineEdit(pagesupprimer_2);
        idsupprimer_2->setObjectName("idsupprimer_2");
        idsupprimer_2->setGeometry(QRect(330, 150, 201, 41));
        label_22 = new QLabel(pagesupprimer_2);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(160, 150, 161, 41));
        label_22->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stackedWidgetemploye->addWidget(pagesupprimer_2);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_41 = new QLabel(page_2);
        label_41->setObjectName("label_41");
        label_41->setGeometry(QRect(110, 180, 151, 31));
        label_41->setFont(font);
        receiveddata = new QTextEdit(page_2);
        receiveddata->setObjectName("receiveddata");
        receiveddata->setGeometry(QRect(110, 220, 171, 51));
        stackedWidgetemploye->addWidget(page_2);
        pageajouteremploye_2 = new QWidget();
        pageajouteremploye_2->setObjectName("pageajouteremploye_2");
        bouttonajouter_2 = new QPushButton(pageajouteremploye_2);
        bouttonajouter_2->setObjectName("bouttonajouter_2");
        bouttonajouter_2->setGeometry(QRect(290, 360, 161, 51));
        frame_10 = new QFrame(pageajouteremploye_2);
        frame_10->setObjectName("frame_10");
        frame_10->setGeometry(QRect(180, 40, 169, 291));
        frame_10->setFrameShape(QFrame::Shape::StyledPanel);
        frame_10->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_10);
        verticalLayout_9->setObjectName("verticalLayout_9");
        label_10 = new QLabel(frame_10);
        label_10->setObjectName("label_10");
        label_10->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(label_10);

        label_12 = new QLabel(frame_10);
        label_12->setObjectName("label_12");
        label_12->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(label_12);

        label_13 = new QLabel(frame_10);
        label_13->setObjectName("label_13");
        label_13->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(label_13);

        label_24 = new QLabel(frame_10);
        label_24->setObjectName("label_24");
        label_24->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(label_24);

        label_25 = new QLabel(frame_10);
        label_25->setObjectName("label_25");
        label_25->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(label_25);

        label_26 = new QLabel(frame_10);
        label_26->setObjectName("label_26");
        label_26->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(label_26);

        label_27 = new QLabel(frame_10);
        label_27->setObjectName("label_27");
        label_27->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_9->addWidget(label_27);

        frame_11 = new QFrame(pageajouteremploye_2);
        frame_11->setObjectName("frame_11");
        frame_11->setGeometry(QRect(380, 40, 221, 291));
        frame_11->setFrameShape(QFrame::Shape::StyledPanel);
        frame_11->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_10 = new QVBoxLayout(frame_11);
        verticalLayout_10->setObjectName("verticalLayout_10");
        ajouternom_2 = new QLineEdit(frame_11);
        ajouternom_2->setObjectName("ajouternom_2");

        verticalLayout_10->addWidget(ajouternom_2);

        ajouterprenom_2 = new QLineEdit(frame_11);
        ajouterprenom_2->setObjectName("ajouterprenom_2");

        verticalLayout_10->addWidget(ajouterprenom_2);

        ajoutermail_2 = new QLineEdit(frame_11);
        ajoutermail_2->setObjectName("ajoutermail_2");

        verticalLayout_10->addWidget(ajoutermail_2);

        ajoutermotdepasse_2 = new QLineEdit(frame_11);
        ajoutermotdepasse_2->setObjectName("ajoutermotdepasse_2");

        verticalLayout_10->addWidget(ajoutermotdepasse_2);

        combogenre_3 = new QComboBox(frame_11);
        combogenre_3->addItem(QString());
        combogenre_3->addItem(QString());
        combogenre_3->setObjectName("combogenre_3");

        verticalLayout_10->addWidget(combogenre_3);

        ajouternumtel_2 = new QLineEdit(frame_11);
        ajouternumtel_2->setObjectName("ajouternumtel_2");

        verticalLayout_10->addWidget(ajouternumtel_2);

        ajouteradresse_2 = new QLineEdit(frame_11);
        ajouteradresse_2->setObjectName("ajouteradresse_2");

        verticalLayout_10->addWidget(ajouteradresse_2);

        stackedWidgetemploye->addWidget(pageajouteremploye_2);
        pagemodifieremloye_2 = new QWidget();
        pagemodifieremloye_2->setObjectName("pagemodifieremloye_2");
        frame_12 = new QFrame(pagemodifieremloye_2);
        frame_12->setObjectName("frame_12");
        frame_12->setGeometry(QRect(540, 40, 211, 341));
        frame_12->setFrameShape(QFrame::Shape::StyledPanel);
        frame_12->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_11 = new QVBoxLayout(frame_12);
        verticalLayout_11->setObjectName("verticalLayout_11");
        ajouternom_4 = new QLineEdit(frame_12);
        ajouternom_4->setObjectName("ajouternom_4");

        verticalLayout_11->addWidget(ajouternom_4);

        ajouterprenom_4 = new QLineEdit(frame_12);
        ajouterprenom_4->setObjectName("ajouterprenom_4");

        verticalLayout_11->addWidget(ajouterprenom_4);

        ajoutermail_4 = new QLineEdit(frame_12);
        ajoutermail_4->setObjectName("ajoutermail_4");

        verticalLayout_11->addWidget(ajoutermail_4);

        combogenre_4 = new QComboBox(frame_12);
        combogenre_4->addItem(QString());
        combogenre_4->addItem(QString());
        combogenre_4->setObjectName("combogenre_4");

        verticalLayout_11->addWidget(combogenre_4);

        ajoutermotdepasse_4 = new QLineEdit(frame_12);
        ajoutermotdepasse_4->setObjectName("ajoutermotdepasse_4");

        verticalLayout_11->addWidget(ajoutermotdepasse_4);

        ajouternumtel_4 = new QLineEdit(frame_12);
        ajouternumtel_4->setObjectName("ajouternumtel_4");

        verticalLayout_11->addWidget(ajouternumtel_4);

        ajouteradresse_4 = new QLineEdit(frame_12);
        ajouteradresse_4->setObjectName("ajouteradresse_4");

        verticalLayout_11->addWidget(ajouteradresse_4);

        bouttonconfirmermodif_2 = new QPushButton(pagemodifieremloye_2);
        bouttonconfirmermodif_2->setObjectName("bouttonconfirmermodif_2");
        bouttonconfirmermodif_2->setGeometry(QRect(440, 390, 161, 51));
        frame_13 = new QFrame(pagemodifieremloye_2);
        frame_13->setObjectName("frame_13");
        frame_13->setGeometry(QRect(350, 40, 169, 341));
        frame_13->setFrameShape(QFrame::Shape::StyledPanel);
        frame_13->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_12 = new QVBoxLayout(frame_13);
        verticalLayout_12->setObjectName("verticalLayout_12");
        label_28 = new QLabel(frame_13);
        label_28->setObjectName("label_28");
        label_28->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_12->addWidget(label_28);

        label_29 = new QLabel(frame_13);
        label_29->setObjectName("label_29");
        label_29->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_12->addWidget(label_29);

        label_30 = new QLabel(frame_13);
        label_30->setObjectName("label_30");
        label_30->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_12->addWidget(label_30);

        label_31 = new QLabel(frame_13);
        label_31->setObjectName("label_31");
        label_31->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_12->addWidget(label_31);

        label_32 = new QLabel(frame_13);
        label_32->setObjectName("label_32");
        label_32->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_12->addWidget(label_32);

        label_33 = new QLabel(frame_13);
        label_33->setObjectName("label_33");
        label_33->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_12->addWidget(label_33);

        label_34 = new QLabel(frame_13);
        label_34->setObjectName("label_34");
        label_34->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_12->addWidget(label_34);

        idemployemodif_2 = new QLineEdit(pagemodifieremloye_2);
        idemployemodif_2->setObjectName("idemployemodif_2");
        idemployemodif_2->setGeometry(QRect(120, 40, 91, 31));
        bouttonconfirmeidmodif = new QPushButton(pagemodifieremloye_2);
        bouttonconfirmeidmodif->setObjectName("bouttonconfirmeidmodif");
        bouttonconfirmeidmodif->setGeometry(QRect(220, 40, 101, 31));
        label_35 = new QLabel(pagemodifieremloye_2);
        label_35->setObjectName("label_35");
        label_35->setGeometry(QRect(10, 40, 101, 31));
        label_35->setAlignment(Qt::AlignmentFlag::AlignCenter);
        stackedWidgetemploye->addWidget(pagemodifieremloye_2);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        gridLayout_5 = new QGridLayout(page_4);
        gridLayout_5->setObjectName("gridLayout_5");
        textHistorique_2 = new QTextEdit(page_4);
        textHistorique_2->setObjectName("textHistorique_2");

        gridLayout_5->addWidget(textHistorique_2, 0, 0, 1, 1);

        stackedWidgetemploye->addWidget(page_4);
        pagestatistiques_2 = new QWidget();
        pagestatistiques_2->setObjectName("pagestatistiques_2");
        stackedWidgetemploye->addWidget(pagestatistiques_2);
        label_40 = new QLabel(pageemp);
        label_40->setObjectName("label_40");
        label_40->setGeometry(QRect(0, 0, 1171, 751));
        label_40->setStyleSheet(QString::fromUtf8(""));
        label_40->setPixmap(QPixmap(QString::fromUtf8(":/images/bg.jpeg")));
        label_40->setScaledContents(true);
        bouttonexportpdf = new QPushButton(pageemp);
        bouttonexportpdf->setObjectName("bouttonexportpdf");
        bouttonexportpdf->setGeometry(QRect(440, 640, 151, 41));
        QFont font1;
        font1.setPointSize(12);
        bouttonexportpdf->setFont(font1);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/pdf.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouttonexportpdf->setIcon(icon6);
        bouttonformlogin = new QPushButton(pageemp);
        bouttonformlogin->setObjectName("bouttonformlogin");
        bouttonformlogin->setGeometry(QRect(1030, 20, 101, 81));
        bouttonformlogin->setCursor(QCursor(Qt::PointingHandCursor));
        bouttonformlogin->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"        background-color: transparent;\n"
"        border: 2px solid transparent;\n"
"        padding: 10px;\n"
"        font-size: 16px;\n"
"    }\n"
"    QPushButton:hover {\n"
"        border: 2px solid rgba(0, 0, 0, 0.3); \n"
"    }\n"
"    QPushButton:pressed {\n"
"        transform: translate(5px, 5px);\n"
"        border: 2px solid rgba(0, 0, 0, 0.1); \n"
"    }"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/homepageicon.png"), QSize(), QIcon::Normal, QIcon::Off);
        bouttonformlogin->setIcon(icon7);
        bouttonformlogin->setIconSize(QSize(70, 70));
        pushButton = new QPushButton(pageemp);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(780, 640, 131, 41));
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(pageemp);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(610, 640, 151, 41));
        pushButton_2->setFont(font);
        stackedWidgetprincipale->addWidget(pageemp);
        label_40->raise();
        frame_3->raise();
        stackedWidgetemploye->raise();
        bouttonexportpdf->raise();
        bouttonformlogin->raise();
        pushButton->raise();
        pushButton_2->raise();
        pageconnection = new QWidget();
        pageconnection->setObjectName("pageconnection");
        pageconnection->setStyleSheet(QString::fromUtf8("\n"
"background-image:none;"));
        bouttonconnection = new QPushButton(pageconnection);
        bouttonconnection->setObjectName("bouttonconnection");
        bouttonconnection->setGeometry(QRect(490, 450, 141, 45));
        QFont font2;
        font2.setBold(true);
        bouttonconnection->setFont(font2);
        bouttonconnection->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"        padding: 10px;\n"
"        font-size: 16px;\n"
"        border: 2px solid rgb(130, 234, 255); \n"
"        transition: background-color 0.2s ease, color 0.2s ease;\n"
"		border-radius:25px;rgb(176, 176, 176)\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: lightblue;\n"
"        border: 2px solid rgba(0, 0, 0, 0.2);\n"
"    }\n"
"    QPushButton:pressed {\n"
"        background-color: #add8e6;\n"
"        border: 2px solid rgba(0, 0, 0, 0.3); \n"
"    }"));
        frame_15 = new QFrame(pageconnection);
        frame_15->setObjectName("frame_15");
        frame_15->setGeometry(QRect(564, 300, 231, 119));
        frame_15->setStyleSheet(QString::fromUtf8("background:lightgrayrgb(244, 253, 255);\n"
"border:none;"));
        frame_15->setFrameShape(QFrame::Shape::StyledPanel);
        frame_15->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_14 = new QVBoxLayout(frame_15);
        verticalLayout_14->setObjectName("verticalLayout_14");
        inputloginform_2 = new QLineEdit(frame_15);
        inputloginform_2->setObjectName("inputloginform_2");
        inputloginform_2->setMinimumSize(QSize(0, 45));
        inputloginform_2->setStyleSheet(QString::fromUtf8("padding:10px;\n"
""));

        verticalLayout_14->addWidget(inputloginform_2);

        inputloginmotdepasse_2 = new QLineEdit(frame_15);
        inputloginmotdepasse_2->setObjectName("inputloginmotdepasse_2");
        inputloginmotdepasse_2->setMinimumSize(QSize(0, 45));
        inputloginmotdepasse_2->setStyleSheet(QString::fromUtf8("padding:10px;"));

        verticalLayout_14->addWidget(inputloginmotdepasse_2);

        frame_14 = new QFrame(pageconnection);
        frame_14->setObjectName("frame_14");
        frame_14->setGeometry(QRect(330, 300, 231, 121));
        frame_14->setStyleSheet(QString::fromUtf8("background:lightgrayrgb(244, 253, 255);\n"
"border:none;"));
        frame_14->setFrameShape(QFrame::Shape::StyledPanel);
        frame_14->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_13 = new QVBoxLayout(frame_14);
        verticalLayout_13->setObjectName("verticalLayout_13");
        label_36 = new QLabel(frame_14);
        label_36->setObjectName("label_36");
        label_36->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";\n"
"background-color:whitesmoke;\n"
"border-radius:25px;\n"
"border: 2px solid rgb(130, 234, 255); "));
        label_36->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_13->addWidget(label_36);

        label_37 = new QLabel(frame_14);
        label_37->setObjectName("label_37");
        label_37->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";\n"
"background-color:whitesmoke;\n"
"   border: 2px solid rgb(130, 234, 255); \n"
"border-radius:25px;"));
        label_37->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_13->addWidget(label_37);

        label_38 = new QLabel(pageconnection);
        label_38->setObjectName("label_38");
        label_38->setGeometry(QRect(0, 0, 1171, 751));
        label_38->setStyleSheet(QString::fromUtf8("\n"
"background-image:url(/images/backgroundacceuil.png);"));
        label_38->setPixmap(QPixmap(QString::fromUtf8(":/images/bg.jpeg")));
        label_38->setScaledContents(true);
        stackedWidgetprincipale->addWidget(pageconnection);
        label_38->raise();
        frame_15->raise();
        frame_14->raise();
        bouttonconnection->raise();
        pagehomepage = new QWidget();
        pagehomepage->setObjectName("pagehomepage");
        pagehomepage->setStyleSheet(QString::fromUtf8(""));
        frame_16 = new QFrame(pagehomepage);
        frame_16->setObjectName("frame_16");
        frame_16->setGeometry(QRect(799, 190, 291, 431));
        frame_16->setFrameShape(QFrame::Shape::StyledPanel);
        frame_16->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_15 = new QVBoxLayout(frame_16);
        verticalLayout_15->setObjectName("verticalLayout_15");
        bouttonaffichergestionemp = new QPushButton(frame_16);
        bouttonaffichergestionemp->setObjectName("bouttonaffichergestionemp");
        bouttonaffichergestionemp->setMinimumSize(QSize(0, 40));
        bouttonaffichergestionemp->setFont(font);
        bouttonaffichergestionemp->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"        padding: 10px;\n"
"        font-size: 16px;\n"
"        border: 2px solid rgb(130, 234, 255); \n"
"        transition: background-color 0.2s ease, color 0.2s ease;\n"
"		border-radius:25px;rgb(176, 176, 176)\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: lightblue;\n"
"        border: 2px solid rgba(0, 0, 0, 0.2);\n"
"    }\n"
"    QPushButton:pressed {\n"
"background-color:rgba(3,75,88,255);\n"
"        border: 2px solid rgba(0, 0, 0, 0.3); \n"
"    }"));
        bouttonaffichergestionemp->setIconSize(QSize(20, 20));

        verticalLayout_15->addWidget(bouttonaffichergestionemp);

        pushButton_4 = new QPushButton(frame_16);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(0, 40));
        pushButton_4->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"        padding: 10px;\n"
"        font-size: 16px;\n"
"        border: 2px solid rgb(130, 234, 255); \n"
"        transition: background-color 0.2s ease, color 0.2s ease;\n"
"		border-radius:25px;rgb(176, 176, 176)\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: lightblue;\n"
"        border: 2px solid rgba(0, 0, 0, 0.2);\n"
"    }\n"
"    QPushButton:pressed {\n"
"background-color:rgba(3,75,88,255);\n"
"        border: 2px solid rgba(0, 0, 0, 0.3); \n"
"    }"));

        verticalLayout_15->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(frame_16);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(0, 40));

        verticalLayout_15->addWidget(pushButton_5);

        pushButton_8 = new QPushButton(frame_16);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setMinimumSize(QSize(0, 40));
        pushButton_8->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"        padding: 10px;\n"
"        font-size: 16px;\n"
"        border: 2px solid rgb(130, 234, 255); \n"
"        transition: background-color 0.2s ease, color 0.2s ease;\n"
"		border-radius:25px;rgb(176, 176, 176)\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: lightblue;\n"
"        border: 2px solid rgba(0, 0, 0, 0.2);\n"
"    }\n"
"    QPushButton:pressed {\n"
"background-color:rgba(3,75,88,255);\n"
"        border: 2px solid rgba(0, 0, 0, 0.3); \n"
"    }"));

        verticalLayout_15->addWidget(pushButton_8);

        pushButton_9 = new QPushButton(frame_16);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setMinimumSize(QSize(0, 40));
        pushButton_9->setStyleSheet(QString::fromUtf8(" QPushButton {\n"
"        padding: 10px;\n"
"        font-size: 16px;\n"
"        border: 2px solid rgb(130, 234, 255); \n"
"        transition: background-color 0.2s ease, color 0.2s ease;\n"
"		border-radius:25px;rgb(176, 176, 176)\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: lightblue;\n"
"        border: 2px solid rgba(0, 0, 0, 0.2);\n"
"    }\n"
"    QPushButton:pressed {\n"
"background-color:rgba(3,75,88,255);\n"
"        border: 2px solid rgba(0, 0, 0, 0.3); \n"
"    }"));

        verticalLayout_15->addWidget(pushButton_9);

        label_39 = new QLabel(pagehomepage);
        label_39->setObjectName("label_39");
        label_39->setGeometry(QRect(0, 0, 1171, 751));
        label_39->setPixmap(QPixmap(QString::fromUtf8(":/images/backgroundacceuil.png")));
        label_39->setScaledContents(true);
        stackedWidgetprincipale->addWidget(pagehomepage);
        label_39->raise();
        frame_16->raise();

        gridLayout_3->addWidget(stackedWidgetprincipale, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidgetprincipale->setCurrentIndex(2);
        stackedWidgetemploye->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        bouttonafficheremloyes_2->setText(QCoreApplication::translate("MainWindow", "Afficher Employes", nullptr));
        bouttonafficherajoutemploye_2->setText(QCoreApplication::translate("MainWindow", "Ajouter Employe", nullptr));
        bouttonafficherpagemodifieremploye_2->setText(QCoreApplication::translate("MainWindow", "Modifier Employe", nullptr));
        bouttonafficherpagesupprimer_2->setText(QCoreApplication::translate("MainWindow", "Supprimer Employe", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Param\303\251tres", nullptr));
        bouttonrecherche_2->setText(QCoreApplication::translate("MainWindow", "Recherche", nullptr));
        buttontriparnom_2->setText(QCoreApplication::translate("MainWindow", "tri par Nom", nullptr));
        button_supprimer_2->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Id Produit", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "Donn\303\251es Recues :", nullptr));
        bouttonajouter_2->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "mail", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "mot de passe", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "genre", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "num\303\251ro de t\303\251l\303\250phone", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        combogenre_3->setItemText(0, QCoreApplication::translate("MainWindow", "male", nullptr));
        combogenre_3->setItemText(1, QCoreApplication::translate("MainWindow", "female", nullptr));

        combogenre_4->setItemText(0, QCoreApplication::translate("MainWindow", "male", nullptr));
        combogenre_4->setItemText(1, QCoreApplication::translate("MainWindow", "female", nullptr));

        bouttonconfirmermodif_2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "Prenom", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "mail", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "genre", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "mot de passe", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "num\303\251ro de t\303\251l\303\250phone", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "Adresse", nullptr));
        bouttonconfirmeidmodif->setText(QCoreApplication::translate("MainWindow", "confirmer", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "Id Produit", nullptr));
        label_40->setText(QString());
        bouttonexportpdf->setText(QCoreApplication::translate("MainWindow", "Export PDF", nullptr));
        bouttonformlogin->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Historique", nullptr));
        bouttonconnection->setText(QCoreApplication::translate("MainWindow", "Se Connecter", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "Email / Username", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Mot de passe", nullptr));
        label_38->setText(QString());
        bouttonaffichergestionemp->setText(QCoreApplication::translate("MainWindow", "Employe", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Equipement", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "AAA", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "BBB", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "CCC", nullptr));
        label_39->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
