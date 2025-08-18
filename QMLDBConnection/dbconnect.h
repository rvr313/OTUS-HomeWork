#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QObject>
#include <QSqlDatabase>

class DbConnect : public QObject
{
    Q_OBJECT
public:
    explicit DbConnect(QObject *parent = nullptr);

public slots:
    Q_INVOKABLE void connectDb();

signals:
    void dbConnected();

private:
    QSqlDatabase *db{nullptr};
};

#endif // DBCONNECT_H
