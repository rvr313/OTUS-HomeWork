#include "tablemodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

TableModel::TableModel(QObject *parent)
    : QSqlTableModel{parent}
{
//    setHeaderData(0, Qt::Horizontal, "Date Time");
//    setHeaderData(1, Qt::Horizontal, "Purchase Price");
//    setHeaderData(2, Qt::Horizontal, "Sell Price");
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }
    if (role == Roles::ChangingPriceRole) {
        if (index.row() > 0) {
            bool ok{true};
            double price = index.data().toDouble(&ok);
            QModelIndex previ = index.model()->index(index.row() - 1, index.column(), index.parent());
            double prevp = previ.data().toDouble(&ok);
            if (price < prevp) {
                return QVariant(-1);
            } else if (prevp < price) {
                return QVariant(1);
            }
            return QVariant(0);
        }
    } else if (role > Qt::UserRole) {
        int column_id = role - Qt::UserRole - 1;
        QModelIndex role_index = this->index(index.row(), column_id);
        return QSqlTableModel::data(role_index, Qt::DisplayRole);
    }

    return QSqlTableModel::data(index, role);
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> role_names;
    for (int i = 0; i < m_roles.size(); ++i) {
        auto user_role_id = Qt::UserRole + i + 1;
        role_names[user_role_id] = m_roles.at(i).toLatin1();
    }
    return role_names;
}

void TableModel::allDataChanged()
{
    setTable("Gold");
    setEditStrategy(QSqlTableModel::OnFieldChange);

    if (!select()) {
        qDebug() <<  "Select error";
    }

    QModelIndex top_left = this->index(0, 0);
    QModelIndex bottom_right = this->index(rowCount() - 1, columnCount() - 1);
    emit dataChanged(top_left, bottom_right);
}

int TableModel::getPriceMove(int row, int col) const
{
    QModelIndex index = this->index(row, col);
    if (index.isValid()) {
        bool ok;
        if (int res = data(index, Roles::ChangingPriceRole).toInt(&ok); ok) {
            return res;
        }
    }
    return 0;
}
