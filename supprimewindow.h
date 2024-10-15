#ifndef SUPPRIMEWINDOW_H
#define SUPPRIMEWINDOW_H

#include <QWidget>

class SupprimeWindow : public QWidget {
    Q_OBJECT

public:
    explicit SupprimeWindow(QWidget *parent = nullptr);
    ~SupprimeWindow();
};

#endif // SUPPRIMEWINDOW_H
