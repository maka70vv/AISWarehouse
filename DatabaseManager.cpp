#include "DatabaseManager.h"
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager() : port(5432) {}

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
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(databaseName);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных через QSqlDatabase:" << db.lastError().text();
        return false;
    }

    qDebug() << "Успешное подключение к базе данных через QSqlDatabase";
    return true;
}

void DatabaseManager::closeDatabase() {
    if (QSqlDatabase::contains()) {
        QSqlDatabase::database().close();
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }
}

// Работа с товарами
bool DatabaseManager::addProduct(const QString &name, const QString &sku, int categoryId, const QString &description, const QString &unit, double price, int quantity) {
    QSqlQuery query;
    query.prepare("INSERT INTO products (name, sku, category_id, description, unit, price, quantity) "
                  "VALUES (:name, :sku, :category_id, :description, :unit, :price, :quantity)");
    query.bindValue(":name", name);
    query.bindValue(":sku", sku);
    query.bindValue(":category_id", categoryId);
    query.bindValue(":description", description);
    query.bindValue(":unit", unit);
    query.bindValue(":price", price);
    query.bindValue(":quantity", quantity);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления товара:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseManager::getProducts() {
    QSqlQuery query;
    if (!query.exec("SELECT product_id, name, sku, category_id, description, unit, price, quantity FROM products")) {
        qDebug() << "Ошибка выполнения запроса на выборку товаров:" << query.lastError().text();
    }
    return query;
}

// Работа с категориями
bool DatabaseManager::addCategory(const QString &name, const QString &description) {
    QSqlQuery query;
    query.prepare("INSERT INTO categories (name, description) VALUES (:name, :description)");
    query.bindValue(":name", name);
    query.bindValue(":description", description);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления категории:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQuery DatabaseManager::getCategories() {
    QSqlQuery query;
    if (!query.exec("SELECT category_id, name, description FROM categories")) {
        qDebug() << "Ошибка выполнения запроса на выборку категорий:" << query.lastError().text();
    }
    return query;
}
