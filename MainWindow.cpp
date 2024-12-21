#include "MainWindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFormLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    initializeUI();
    setupConnections();
    dbManager.connectToDatabase(); // Подключение к базе данных при запуске
}

MainWindow::~MainWindow() {
    dbManager.closeDatabase();
}

void MainWindow::initializeUI() {
    auto *layout = new QVBoxLayout;

    productTable = new QTableWidget(this);
    productTable->setColumnCount(5);
    productTable->setHorizontalHeaderLabels({"Name", "SKU", "Category", "Price", "Quantity"});

    addButton = new QPushButton("Add Product", this);
    editButton = new QPushButton("Edit Product", this);
    deleteButton = new QPushButton("Delete Product", this);
    reportButton = new QPushButton("Generate Report", this);
    dbConfigButton = new QPushButton("Database Config", this);

    layout->addWidget(productTable);
    layout->addWidget(addButton);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
    layout->addWidget(reportButton);
    layout->addWidget(dbConfigButton);

    auto *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

void MainWindow::setupConnections() {
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addProduct);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editProduct);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteProduct);
    connect(reportButton, &QPushButton::clicked, this, &MainWindow::generateReport);
    connect(dbConfigButton, &QPushButton::clicked, this, &MainWindow::openDatabaseDialog);
}

void MainWindow::openDatabaseDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Database Configuration");

    QFormLayout form(&dialog);
    QLineEdit *hostEdit = new QLineEdit(&dialog);
    QLineEdit *portEdit = new QLineEdit(&dialog);
    QLineEdit *userEdit = new QLineEdit(&dialog);
    QLineEdit *passwordEdit = new QLineEdit(&dialog);

    form.addRow("Host:", hostEdit);
    form.addRow("Port:", portEdit);
    form.addRow("User:", userEdit);
    form.addRow("Password:", passwordEdit);

    QPushButton *okButton = new QPushButton("OK", &dialog);
    QPushButton *cancelButton = new QPushButton("Cancel", &dialog);
    QHBoxLayout buttons;
    buttons.addWidget(okButton);
    buttons.addWidget(cancelButton);

    form.addRow(&buttons);

    connect(okButton, &QPushButton::clicked, [&]() {
        dbManager.setConnectionDetails(
            hostEdit->text(),
            portEdit->text().toInt(),
            userEdit->text(),
            passwordEdit->text()
        );
        dialog.accept();
    });

    connect(cancelButton, &QPushButton::clicked, [&]() {
        dialog.reject();
    });

    dialog.exec();
}

void MainWindow::addProduct() {
    // Реализация добавления товара
}

void MainWindow::editProduct() {
    // Реализация редактирования товара
}

void MainWindow::deleteProduct() {
    // Реализация удаления товара
}

void MainWindow::generateReport() {
    // Реализация генерации отчета
}
