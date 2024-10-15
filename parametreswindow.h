#ifndef PARAMETRESWINDOW_H
#define PARAMETRESWINDOW_H

#include <QWidget>

class ParametresWindow : public QWidget {
    Q_OBJECT

public:
    explicit ParametresWindow(QWidget *parent = nullptr);
    ~ParametresWindow();
};

#endif // PARAMETRESWINDOW_H
