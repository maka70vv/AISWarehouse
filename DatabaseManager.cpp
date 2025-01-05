#include "DatabaseManager.h"
#include <QDebug>

DatabaseManager::DatabaseManager() : conn(nullptr), port(5432) {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

void DatabaseManager::setConnectionDetails(const QString &host, int port, const QString &user, const QString &password) {
    this->host = host;
    this->port = port;
    this->user = user;
    this->password = password;
}

void DatabaseManager::setDatabaseName(const QString &databaseName) {
    this->databaseName = databaseName;
}

bool DatabaseManager::connectToDatabase() {
    QString connInfo = QString("user=%1 password=%2 dbname=%3 hostaddr=%4 port=%5")
        .arg(user)          // Имя пользователя
        .arg(password)      // Пароль
        .arg(databaseName)  // Имя базы данных
        .arg(host)          // Адрес хоста (hostaddr)
        .arg(port);         // Порт


    // conn = PQconnectdb(connInfo.toUtf8().constData());

    conn = PQconnectdb("user=postgres password=123 dbname=warehouse hostaddr=127.0.0.1 port=5432");


    if (PQstatus(conn) != CONNECTION_OK) {
        qDebug() << "Ошибка подключения к базе данных:" << PQerrorMessage(conn);
        return false;
    }

    qDebug() << "Успешное подключение к базе данных";
    return true;
}

void DatabaseManager::closeDatabase() {
    if (conn) {
        PQfinish(conn);
        conn = nullptr;
    }
}
