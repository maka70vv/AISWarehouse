#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDialog>
#include "DatabaseManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
        void openDatabaseDialog();
    void addProduct();
    void editProduct();
    void deleteProduct();
    void generateReport();

private:
    QTableWidget *productTable;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *reportButton;
    QPushButton *dbConfigButton;
    DatabaseManager dbManager;

    void initializeUI();
    void setupConnections();
};

#endif // MAINWINDOW_H
