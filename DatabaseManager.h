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

private:
    PGconn *conn;
};

#endif