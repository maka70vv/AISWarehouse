#include "DatabaseManager.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

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

bool DatabaseManager::editProduct(int productId, const QString &name, const QString &sku, int categoryId, const QString &description, const QString &unit, double price, int quantity) {
    QSqlQuery query;
    query.prepare("UPDATE products SET name = :name, sku = :sku, category_id = :category_id, description = :description, "
                  "unit = :unit, price = :price, quantity = :quantity WHERE product_id = :product_id");
    query.bindValue(":name", name);
    query.bindValue(":sku", sku);
    query.bindValue(":category_id", categoryId);
    query.bindValue(":description", description);
    query.bindValue(":unit", unit);
    query.bindValue(":price", price);
    query.bindValue(":quantity", quantity);
    query.bindValue(":product_id", productId);

    if (!query.exec()) {
        qDebug() << "Ошибка редактирования товара:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::deleteProduct(int productId) {
    QSqlQuery query;
    query.prepare("DELETE FROM products WHERE product_id = :product_id");
    query.bindValue(":product_id", productId);

    if (!query.exec()) {
        qDebug() << "Ошибка удаления товара:" << query.lastError().text();
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

// Операции учета
bool DatabaseManager::registerIncoming(int productId, int warehouseId, int quantity, const QString &reason) {
    QSqlQuery query;
    query.prepare("INSERT INTO inventory_operations (product_id, warehouse_id, operation_type, quantity, reason) "
                  "VALUES (:product_id, :warehouse_id, 'incoming', :quantity, :reason)");
    query.bindValue(":product_id", productId);
    query.bindValue(":warehouse_id", warehouseId);
    query.bindValue(":quantity", quantity);
    query.bindValue(":reason", reason);

    if (!query.exec()) {
        qDebug() << "Ошибка регистрации поступления:" << query.lastError().text();
        return false;
    }

    return true;
}
