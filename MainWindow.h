#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "DatabaseManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTabWidget *tabWidget;
    QWidget *productsTab, *operationsTab, *usersTab, *reportsTab;

    DatabaseManager dbManager;

    // Методы для настройки вкладок
    void setupTabs();
    void setupProductsUI(QWidget *parent);
    void setupOperationsUI(QWidget *parent);
    void setupUsersUI(QWidget *parent);
    void setupReportsUI(QWidget *parent);

    // Метод обновления таблицы товаров
    void updateProductsTable();
};

#endif // MAINWINDOW_H
