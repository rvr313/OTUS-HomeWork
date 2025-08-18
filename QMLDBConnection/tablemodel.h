#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <qqml.h>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
    QML_ELEMENT
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
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

public slots:
    void allDataChanged();

private:
    QStringList m_headers = {tr("Date Time"), tr("Purchase Price"), tr("Sell Price")};
    QStringList m_roles = {"datetime", "purchase", "sell", "changing"};
};

#endif // TABLEMODEL_H
