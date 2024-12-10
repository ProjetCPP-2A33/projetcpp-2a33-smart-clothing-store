#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QPixmap>

class ImageDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ImageDelegate(QObject *parent = nullptr);
    ~ImageDelegate() override = default;

    // Fonction pour dessiner l'image dans le tableau
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // Fonction pour déterminer la taille de l'image dans la cellule
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // IMAGEDELEGATE_H
