#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlTableModel>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    enum Roles {
        DateTimeRole = Qt::UserRole + 1,
        PurchasePriceRole,
        SellPriceRole,
        ChangingPriceRole
    };

public:
    explicit TableModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void allDataChanged();
    int getPriceMove(int row, int col) const;

private:
    QStringList m_roles = {"datetime", "purchase", "sell", "changing"};
};

#endif // TABLEMODEL_H
