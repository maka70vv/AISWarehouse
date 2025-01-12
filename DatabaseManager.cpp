#include "DatabaseManager.h"
#include <QSqlError>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

DatabaseManager::DatabaseManager() : port(5432) {}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

std::vector<std::map<QString, QString>> DatabaseManager::fetchDataForReport(const QString &tableName) {
    std::vector<std::map<QString, QString>> data;

    // Формируем SQL-запрос с использованием имени таблицы
    QSqlQuery query;
    query.prepare("SELECT * FROM " + tableName);

    if (!query.exec()) {
        qDebug() << "Failed to execute query for table:" << tableName << "Error:" << query.lastError().text();
        return data; // Возвращаем пустой результат при ошибке
    }

    while (query.next()) {
        QSqlRecord record = query.record();
        std::map<QString, QString> row;
        for (int i = 0; i < record.count(); ++i) {
            row[record.fieldName(i)] = query.value(i).toString();
        }
        data.push_back(row);
    }
    return data;
}


bool DatabaseManager::generateCSVReport(const QString &tableName, const QString &filePath) {
    auto data = fetchDataForReport(tableName);;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing: " << filePath;
        return false;
    }

    QTextStream out(&file);
    if (!data.empty()) {
        // Write header
        for (const auto &header : data[0]) {
            out << header.first << ",";
        }
        out << "\n";

        // Write rows
        for (const auto &row : data) {
            for (const auto &cell : row) {
                out << cell.second << ",";
            }
            out << "\n";
        }
    }

    file.close();
    return true;
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

bool DatabaseManager::editCategory(int categoryId, const QString &name, const QString &description) {
    QSqlQuery query;
    query.prepare("UPDATE categories SET name = :name, description = :description WHERE category_id = :category_id");
    query.bindValue(":name", name);
    query.bindValue(":description", description);
    query.bindValue(":category_id", categoryId);

    if (!query.exec()) {
        qDebug() << "Ошибка редактирования категории:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::deleteCategory(int categoryId) {
    QSqlQuery query;
    query.prepare("DELETE FROM categories WHERE category_id = :category_id");
    query.bindValue(":category_id", categoryId);

    if (!query.exec()) {
        qDebug() << "Ошибка удаления категории:" << query.lastError().text();
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



QSqlQuery DatabaseManager::getOperations() {
    QSqlQuery query;
    if (!query.exec("SELECT operation_id, product_id, warehouse_id, operation_type, quantity, reason, created_at FROM inventory_operations")) {
        qDebug() << "Ошибка выполнения запроса на выборку товаров:" << query.lastError().text();
    }
    return query;
}


bool DatabaseManager::addOperation(int product_id, int warehouse_id, const QString &operation_type, int quantity, const QString &reason) {
    QSqlQuery query;
    query.prepare("INSERT INTO inventory_operations (product_id, warehouse_id, operation_type, quantity, reason) VALUES (:product_id, :warehouse_id, :operation_type, :quantity, :reason)");
    query.bindValue(":product_id", product_id);
    query.bindValue(":operation_type", operation_type);
    query.bindValue(":warehouse_id", warehouse_id);
    query.bindValue(":quantity", quantity);
    query.bindValue(":reason", reason);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления категории:" << query.lastError().text();
        return false;
    }

    return true;
}