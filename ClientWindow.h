#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>

namespace Ui {
class ClientWindow;  // Forward declare Ui::ClientWindow
}

class ClientWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

private:
    Ui::ClientWindow *ui;  // Use Ui::ClientWindow here
};

#endif // CLIENTWINDOW_H
