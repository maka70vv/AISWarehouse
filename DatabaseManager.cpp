#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager() : conn(nullptr), host("localhost"), port(5432), user("admin"), password("admin") {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

void DatabaseManager::setConnectionDetails(const QString &newHost, int newPort, const QString &newUser, const QString &newPassword) {
    host = newHost;
    port = newPort;
    user = newUser;
    password = newPassword;
}

bool DatabaseManager::connectToDatabase() {
    QString connectionString = QString("host=%1 port=%2 user=%3 password=%4 dbname=warehouse")
        .arg(host)
        .arg(port)
        .arg(user)
        .arg(password);

    conn = PQconnectdb(connectionString.toStdString().c_str());

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        return false;
    }

    std::cout << "Connected to database successfully." << std::endl;
    return true;
}

void DatabaseManager::closeDatabase() {
    if (conn) {
        PQfinish(conn);
        conn = nullptr;
    }
}
