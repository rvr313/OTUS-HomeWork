#include "pricedelegate.h"

#include <QPainter>

PriceDelegate::PriceDelegate(QObject *parent)
    : QAbstractItemDelegate{parent}
{}

void PriceDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    bool ok{true};
    double price = index.data().toDouble(&ok);
    PriceMove pmove = PriceMove::NOMOVED;
    if (index.row() > 0) {
        QModelIndex previ = index.model()->index(index.row() - 1, index.column(), index.parent());
        double prevp = previ.data().toDouble(&ok);
        if (price < prevp) {
            pmove = PriceMove::DECREASED;
        } else if (prevp < price) {
            pmove = PriceMove::INCREASED;
        }
    }

    painter->save();
    QRect rec = option.rect;

    double cx = rec.x() + 20;
    double cy = rec.y() + (rec.height() / 2);
    int d = 8;
    int lx = cx - d;
    int rx = cx + d;
    int dy = 4;

    if (pmove == PriceMove::DECREASED) {
        QColor color = Qt::red;
        QPen p(color, 2);
        painter->setPen(p);
        QPoint pc1(cx, cy + d);
        painter->drawLine(QPoint(lx, cy), pc1);
        painter->drawLine(QPoint(rx, cy), pc1);
        QPoint pc2(cx, cy + dy);
        painter->drawLine(QPoint(lx, cy - dy), pc2);
        painter->drawLine(QPoint(rx, cy - dy), pc2);
        painter->drawPoint(QPoint(cx, cy - dy));
        painter->drawPoint(QPoint(cx, cy - d));
    } else if (pmove == PriceMove::INCREASED) {
        QColor color = Qt::darkGreen;
        QPen p(color, 2);
        painter->setPen(p);
        QPoint pc1(cx, cy - d);
        painter->drawLine(QPoint(lx, cy), pc1);
        painter->drawLine(QPoint(rx, cy), pc1);
        QPoint pc2(cx, cy - dy);
        painter->drawLine(QPoint(lx, cy + dy), pc2);
        painter->drawLine(QPoint(rx, cy + dy), pc2);
        painter->drawPoint(QPoint(cx, cy + dy));
        painter->drawPoint(QPoint(cx, cy + d));
    } else { // PriceMove::NOMOVED
        QColor color = Qt::gray;
        QPen p(color, 2);
        painter->setPen(p);
        painter->drawLine(QPoint(lx, cy - 2), QPoint(rx, cy - 2));
        painter->drawLine(QPoint(lx, cy + 2), QPoint(rx, cy + 2));
        painter->drawPoint(QPoint(cx, cy - d));
        painter->drawPoint(QPoint(cx, cy + d));
    }
    QColor textPen = index.data(Qt::DecorationRole).value<QColor>();
    painter->setPen(textPen);
    QRect recText = rec.marginsRemoved(QMargins(0, 8, 10, 0));
    painter->drawText(QRectF(recText), QString("%1").arg(price, 0, 'f', 1), QTextOption(Qt::AlignRight));
    painter->restore();
}

QSize PriceDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(50, 20);
}
