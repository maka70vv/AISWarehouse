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

private:
    QString host;
    int port;
    QString user;
    QString password;
    PGconn *conn;
};

#endif // DATABASEMANAGER_H
