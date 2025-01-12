#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "DatabaseManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addGenerateReportMenu();
    void onGenerateReport();
    ~MainWindow();

private:
    QTabWidget *tabWidget;
    QWidget *productsTab, *categoriesTab, *operationsTab;

    DatabaseManager dbManager;

    // Настройка вкладок
    void setupTabs();
    void setupProductsUI(QWidget *parent);
    void setupCategoriesUI(QWidget *parent);
    void setupOperationsUI(QWidget *parent);

    // Обновление таблиц
    void updateProductsTable();
    void updateCategoriesTable();
    void setupOperationsUi(QWidget* parent);
    void updateOperationsTable();
};

#endif // MAINWINDOW_H
