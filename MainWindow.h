#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "DatabaseManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTabWidget *tabWidget;
    QWidget *productsTab, *categoriesTab;

    DatabaseManager dbManager;

    void setupTabs();
    void setupProductsUI(QWidget *parent);
    void setupCategoriesUI(QWidget *parent);

    void updateProductsTable();
    void updateCategoriesTable();
};

#endif // MAINWINDOW_H
