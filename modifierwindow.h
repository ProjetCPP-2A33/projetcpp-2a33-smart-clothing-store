#ifndef MODIFIERWINDOW_H
#define MODIFIERWINDOW_H

#include <QWidget>

class ModifierWindow : public QWidget {
    Q_OBJECT

public:
    explicit ModifierWindow(QWidget *parent = nullptr);
    ~ModifierWindow();
};

#endif // MODIFIERWINDOW_H
