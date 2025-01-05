#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <libpq-fe.h>

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    bool connectToDatabase();
    void closeDatabase();
    void setConnectionDetails(const QString &host, int port, const QString &user, const QString &password);
    void setDatabaseName(const QString &databaseName);

private:
    QString host;
    int port;
    QString user;
    QString password;
    QString databaseName;
    PGconn *conn;
};

#endif // DATABASEMANAGER_H
