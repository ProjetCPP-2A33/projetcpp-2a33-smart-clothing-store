// accueilwindow.h
#ifndef ACCUEILWINDOW_H
#define ACCUEILWINDOW_H

#include <QWidget>

class AccueilWindow : public QWidget {
    Q_OBJECT

public:
    explicit AccueilWindow(QWidget *parent = nullptr);
    ~AccueilWindow();
};

#endif // ACCUEILWINDOW_H
