#include "dbconnect.h"
#include <QDebug>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

namespace {

bool connectDb()
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.open()) {
        QSqlError err = db.lastError();
        qDebug() << err.nativeErrorCode() << ": " << err.text();
        return false;
    }

    return true;
}

bool importCsvToDb()
{
    const QString csvFile = "../gold.csv";
    QFile file(csvFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open CSV data file - " << csvFile;
        return false;
    }

    bool header{true};
    QTextStream in(&file);


    while (!in.atEnd()) {
        if (header) {
            in.readLine();
            header = false;
        }
        QStringList fields = in.readLine().split(',', Qt::SkipEmptyParts);

        QSqlQuery query;
        if (!query.prepare("INSERT INTO Gold (DateTime, PricePurchase, PriceSell)"
                           "VALUES(:datetime, :pricePurchase, :priceCell)")) {
            qDebug() << query.lastError();
        }

        query.bindValue(":datetime", fields.at(0));
        bool ok;
        if (double pricePurchase = fields.at(1).toDouble(&ok); ok) {
            query.bindValue(":pricePurchase",  pricePurchase);
        } else {
            qDebug() << "Cannot convert purchase price to number - " << fields.at(1);
            continue;
        }
        if (double priceCell = fields.at(2).toDouble(&ok); ok) {
            query.bindValue(":priceCell", priceCell);
        } else {
            qDebug() << "Cannot convert cell price to number - " << fields.at(2);
            continue;
        }

        if (!query.exec()) {
            qDebug() <<  query.lastError();
            continue;
        }
    }

    return true;
}

} // anonymous namespace

DbConnect::DbConnect(QObject *parent) : QObject(parent)
{
    // Nothing else to do.
}

bool DbConnect::connected() const
{
    return m_connected;
}

bool DbConnect::addDatabase()
{
    const QString driverName = "QSQLITE";

    if (!QSqlDatabase::isDriverAvailable(driverName)) {
        qDebug() << "No driver found" << driverName;
        qDebug() << "Available drivers:" <<  QSqlDatabase::drivers();
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(driverName);
    db.setDatabaseName(":memory:");

    return true;
}

void DbConnect::setConnected(bool connected)
{
    if (m_connected == connected)
        return;

    m_connected = connected;
    emit dbConnected();
}

void DbConnect::connectDb()
{
    // Check if DB is already connected.
    if (connected()) {
         return;
     }

    if (!::connectDb()) {
        return;
    }

    QSqlQuery query;
    QString cmd = "CREATE TABLE Gold (DateTime TEXT, PricePurchase REAL, PriceSell REAL);";
    if (!query.prepare(cmd) || !query.exec()) {
        qDebug() << query.lastError();
        return;
    }

    importCsvToDb();

    qDebug() << "DB connected";

    setConnected(true);
}
