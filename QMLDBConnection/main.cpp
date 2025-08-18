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

    DbConnect connection;
    DbConnect::addDatabase();
    TableModel table_model;

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
