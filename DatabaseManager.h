#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlQuery>
#include <QDate>
#include <libpq-fe.h>

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    // Методы подключения
    bool connectToDatabase();
    void closeDatabase();
    void setConnectionDetails(const QString &host, int port, const QString &user, const QString &password);
    void setDatabaseName(const QString &databaseName);

    // Работа с товарами
    bool addProduct(const QString &name, const QString &sku, int categoryId, const QString &description, const QString &unit, double price, int quantity);
    bool editProduct(int productId, const QString &name, const QString &sku, int categoryId, const QString &description, const QString &unit, double price, int quantity);
    bool deleteProduct(int productId);
    QSqlQuery getProducts();

    // Операции учета
    bool registerIncoming(int productId, int warehouseId, int quantity, const QString &reason);
    bool registerOutgoing(int productId, int warehouseId, int quantity, const QString &reason);
    bool transferProduct(int productId, int fromWarehouseId, int toWarehouseId, int quantity);

    // Инвентаризация
    QSqlQuery getInventory();
    bool exportInventoryToCSV(const QString &filePath);

    // Работа с пользователями
    QString getUserRole(const QString &username);

    // Отчеты
    QSqlQuery generateReport(const QString &reportType, const QDate &startDate, const QDate &endDate);
    bool exportReportToCSV(const QString &reportType, const QString &filePath);

private:
    QString host;
    int port;
    QString user;
    QString password;
    QString databaseName;
    PGconn *conn;
};

#endif // DATABASEMANAGER_H
