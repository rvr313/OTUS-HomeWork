#include "tablemodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

TableModel::TableModel(QObject *parent)
    : QSqlTableModel{parent}
{
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole  && orientation == Qt::Horizontal
        && -1 < section && section < m_headers.size()) {
        return m_headers.at(section);
    }

    return {};

}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    constexpr int DOWN = 0;
    constexpr int SAME = 1;
    constexpr int UP = 2;

    auto priceMoveIndex = [&index]() {
        bool ok{true};
        double price = index.data().toDouble(&ok);
        QModelIndex previ = index.model()->index(index.row() - 1, index.column(), index.parent());
        double prevp = previ.data().toDouble(&ok);
        if (price < prevp) {
            return DOWN;
        } else if (prevp < price) {
            return UP;
        }
        return SAME;
    };

    if (role == DisplayTextRole) {
        if (index.column() > 0) {
            bool ok{true};
            double price = index.data().toDouble(&ok);
            return QString("%1").arg(price, 0, 'f', 2);
        }
        return QSqlTableModel::data(index, Qt::DisplayRole);
    } else if (role == Roles::ColorPriceRole) {
        if (index.row() > 0) {
            int pmi = priceMoveIndex();
            return QColor(m_colors[pmi]);
        }
        return QColor(Qt::black);
    } else if (role == Roles::MovementPriceRole) {
        if (index.column() > 0) {
            int pmi = index.row() > 0 ? priceMoveIndex() : SAME;
            return m_movements[pmi];
        }
        return QString();
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
