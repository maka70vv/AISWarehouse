#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager() : conn(nullptr) {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

bool DatabaseManager::connectToDatabase() {
    conn = PQconnectdb("host=localhost dbname=warehouse user=admin password=admin");

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