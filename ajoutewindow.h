// ajoutewindow.h
#ifndef AJOUTEWINDOW_H
#define AJOUTEWINDOW_H

#include <QWidget>

class AjouteWindow : public QWidget {
    Q_OBJECT

public:
    explicit AjouteWindow(QWidget *parent = nullptr);
    ~AjouteWindow();
};

#endif // AJOUTEWINDOW_H
