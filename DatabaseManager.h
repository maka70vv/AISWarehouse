#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    void setConnectionDetails(const QString &host, int port, const QString &user, const QString &password);
    void setDatabaseName(const QString &databaseName);
    bool connectToDatabase();
    void closeDatabase();

    // Работа с товарами
    bool addProduct(const QString &name, const QString &sku, int categoryId, const QString &description, const QString &unit, double price, int quantity);
    bool editProduct(int productId, const QString &name, const QString &sku, int categoryId, const QString &description, const QString &unit, double price, int quantity);
    bool deleteProduct(int productId);
    QSqlQuery getProducts();

    // Работа с категориями
    bool addCategory(const QString &name, const QString &description);
    bool editCategory(int categoryId, const QString &name, const QString &description);
    bool deleteCategory(int categoryId);
    QSqlQuery getCategories();

private:
    QString host;
    int port;
    QString user;
    QString password;
    QString databaseName;
};

#endif // DATABASEMANAGER_H
