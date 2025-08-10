#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pricedelegate.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QDebug>
#include <QFile>

namespace {

bool connectDb()
{
    const QString driverName = "QSQLITE";

    if (!QSqlDatabase::isDriverAvailable(driverName)) {
        qDebug() << "No driver found" << driverName;
        qDebug() << "Available drivers:" <<  QSqlDatabase::drivers();
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(driverName);
    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QSqlError err = db.lastError();
        qDebug() << err.nativeErrorCode() << ": " << err.text();
        return false;
    }

    return true;
}

bool importCsvToDb()
{
    const QString csvFile = "../../gold.csv";
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::connectDb);
    connect(this, &MainWindow::dbConnected, this, &MainWindow::showDbData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectDb()
{
    // Check if DB is already connected.
    if (QSqlDatabase::database().isValid()) {
        return;
    }

    if (!::connectDb()) {
        return;
    }

    {
        QSqlQuery query;
        QString cmd = "CREATE TABLE Gold (DateTime TEXT, PricePurchase REAL, PriceSell REAL);";
        if (!query.prepare(cmd) || !query.exec()) {
            qDebug() << query.lastError();
            return;
        }

        qDebug() << QSqlDatabase::database().tables();
    }

    importCsvToDb();

    {
        QSqlQuery query;

        if (!query.prepare("SELECT * from Gold")) {
            qDebug() << query.lastError();
        }

        if (!query.exec()) {
            qDebug() <<  query.lastError();
        }

#if 0
        int c = 5;
        qDebug() << query.record().count();
        while (query.next() && ((c--) > 0)) {
            qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
        }
#endif
    }

    emit dbConnected();
}

void MainWindow::showDbData()
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("Gold");
    // model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0, Qt::Horizontal, tr("Date Time"));
    model->setHeaderData(1, Qt::Horizontal, tr("Purchase Price"));
    model->setHeaderData(2, Qt::Horizontal, tr("Sell Price"));

    //ui->tableView->setColumnHidden(0, true);
    //ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->resizeColumnToContents(0);
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setModel(model);
    model->select();

    auto *delegate = new PriceDelegate();
    ui->tableView->setItemDelegateForColumn(1, delegate);
    ui->tableView->setItemDelegateForColumn(2, delegate);
    ui->tableView->resizeColumnToContents(0);

}
