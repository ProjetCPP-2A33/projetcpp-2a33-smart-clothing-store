/********************************************************************************
** Form generated from reading UI file 'clientswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTSWINDOW_H
#define UI_CLIENTSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientsWindow
{
public:
    QLabel *label;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QTableView *tableView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QWidget *page_2;
    QWidget *page_3;

    void setupUi(QWidget *ClientsWindow)
    {
        if (ClientsWindow->objectName().isEmpty())
            ClientsWindow->setObjectName("ClientsWindow");
        ClientsWindow->resize(1233, 785);
        label = new QLabel(ClientsWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 1260, 800));
        label->setPixmap(QPixmap(QString::fromUtf8(":/image/Section 9.png")));
        label->setScaledContents(true);
        stackedWidget = new QStackedWidget(ClientsWindow);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(20, 50, 1211, 741));
        page = new QWidget();
        page->setObjectName("page");
        tableView = new QTableView(page);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(290, 60, 901, 271));
        pushButton = new QPushButton(page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(40, 70, 201, 41));
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(40, 140, 201, 41));
        pushButton_3 = new QPushButton(page);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(40, 210, 201, 41));
        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(40, 280, 201, 41));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(720, 420, 471, 271));
        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(240, 420, 471, 271));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        stackedWidget->addWidget(page_3);

        retranslateUi(ClientsWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ClientsWindow);
    } // setupUi

    void retranslateUi(QWidget *ClientsWindow)
    {
        ClientsWindow->setWindowTitle(QCoreApplication::translate("ClientsWindow", "Form", nullptr));
        label->setText(QString());
        pushButton->setText(QCoreApplication::translate("ClientsWindow", "afficher les clients", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ClientsWindow", "ajoutes les clients", nullptr));
        pushButton_3->setText(QCoreApplication::translate("ClientsWindow", "modefer les clients", nullptr));
        pushButton_4->setText(QCoreApplication::translate("ClientsWindow", "supprime les clients", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ClientsWindow", "fonctionnalit\303\251 et notification", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ClientsWindow", "Statistique ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientsWindow: public Ui_ClientsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTSWINDOW_H
