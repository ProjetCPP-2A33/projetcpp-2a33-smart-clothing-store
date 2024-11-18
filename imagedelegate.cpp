#include "imagedelegate.h"
#include <QPixmap>
#include <QDebug>

ImageDelegate::ImageDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.isValid()) {
        QString imagePath = index.data(Qt::DisplayRole).toString();  // Get the image path from the model
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            painter->drawPixmap(option.rect, pixmap);  // Draw the image in the table
        } else {
            // Optionally, draw a placeholder or leave empty if the image is not found
            painter->drawText(option.rect, Qt::AlignCenter, "No photo");
        }
    }
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    // Taille par défaut pour une cellule contenant une image
    return QSize(100, 100);  // Taille fixe pour une mise en page uniforme
}
