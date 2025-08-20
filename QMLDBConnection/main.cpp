#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dbconnect.h"
#include "tablemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    DbConnect connection;
    DbConnect::addDatabase();

    QQmlApplicationEngine engine;

    TableModel table_model;

    QObject::connect(&connection, &DbConnect::dbConnected, &table_model, &TableModel::allDataChanged);

    engine.rootContext()->setContextProperty("dbc", QVariant::fromValue(&connection));
    engine.rootContext()->setContextProperty("table_model", QVariant::fromValue(&table_model));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
