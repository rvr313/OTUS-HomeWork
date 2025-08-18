#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dbconnect.h"
#include "tablemodel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    const QString driverName = "QSQLITE";

    if (!QSqlDatabase::isDriverAvailable(driverName)) {
        qDebug() << "No driver found" << driverName;
        qDebug() << "Available drivers:" <<  QSqlDatabase::drivers();
        return EXIT_FAILURE;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(driverName);
    db.setDatabaseName(":memory:");

    if (db.isValid()) {
        qDebug() << "DB is  valid";
    }
    DbConnect connection;

    TableModel table_model;
    // QSqlTableModel *table_model = new QSqlTableModel();
    // connection.connectDb();
    // table_model->setTable("Gold");
    // table_model->setHeaderData(0, Qt::Horizontal, "Date Time");
    // table_model->setHeaderData(1, Qt::Horizontal, "Purchase Price");
    // table_model->setHeaderData(2, Qt::Horizontal, "Sell Price");
    // table_model->select();

    qmlRegisterType<TableModel>("MyTableModel", 1, 0, "MyTableModel");

    QObject::connect(&connection, &DbConnect::dbConnected, &table_model, &TableModel::allDataChanged);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("dbc", QVariant::fromValue(&connection));
    engine.rootContext()->setContextProperty("table_model", QVariant::fromValue(&table_model));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
