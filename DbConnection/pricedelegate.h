#ifndef PRICEDELEGATE_H
#define PRICEDELEGATE_H

#include <QAbstractItemDelegate>
#include <QObject>

class PriceDelegate : public QAbstractItemDelegate
{
public:
    explicit PriceDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    enum class PriceMove {
        NOMOVED,
        INCREASED,
        DECREASED
    };
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // PRICEDELEGATE_H
