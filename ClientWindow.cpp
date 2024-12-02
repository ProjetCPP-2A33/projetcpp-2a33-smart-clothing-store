#include "ClientWindow.h"            // Correct filename here
#include "ui_ClientWindow.h"         // Correct generated UI header filename

ClientWindow::ClientWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::ClientWindow)
{
    ui->setupUi(this);  // Set up the UI
}

ClientWindow::~ClientWindow()
{
    delete ui;
}
