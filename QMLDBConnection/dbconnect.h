#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QObject>
#include <QSqlDatabase>

class DbConnect : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY dbConnected)
public:
    explicit DbConnect(QObject *parent = nullptr);
    bool connected() const;

    static bool addDatabase();

signals:
    void dbConnected();

public slots:
    void connectDb();

protected slots:
    void setConnected(bool connected);

private:
    QSqlDatabase *db{nullptr};
    bool m_connected{false};
};

#endif // DBCONNECT_H
