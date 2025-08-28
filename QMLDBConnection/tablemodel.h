#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlTableModel>
#include <QList>
#include <QColor>

class TableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    enum Roles {
        DisplayTextRole = Qt::UserRole + 1,
        ColorPriceRole,
        MovementPriceRole
    };

public:
    explicit TableModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void allDataChanged();

private:
    QStringList m_roles = {"text", "color", "movement"};
    QStringList m_headers = {tr("Date Time"), tr("Purchase Price"), tr("Sell Price")};
    QStringList m_movements = {" v ", " = ", " ^ "};
    QList<QColor> m_colors = {Qt::red, Qt::black, Qt::darkGreen};
};

#endif // TABLEMODEL_H
