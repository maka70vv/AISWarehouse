#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <map>
#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <vector>

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

    QSqlQuery getOperations();
    bool addOperation(int product_id, int warehouse_id, const QString& operation_type,
                      int quantity, const QString& reason);

    std::vector<std::map<QString, QString>> fetchDataForReport(const QString &tableName);
    bool generateCSVReport(const QString &tableName, const QString &filePath);


private:
    QString host;
    int port;
    QString user;
    QString password;
    QString databaseName;
};

#endif // DATABASEMANAGER_H
