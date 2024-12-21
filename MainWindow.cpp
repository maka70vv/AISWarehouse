#include "MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *layout = new QVBoxLayout;

    productTable = new QTableWidget(this);
    productTable->setColumnCount(5);
    productTable->setHorizontalHeaderLabels({"Name", "SKU", "Category", "Price", "Quantity"});

    addButton = new QPushButton("Add Product", this);
    editButton = new QPushButton("Edit Product", this);
    deleteButton = new QPushButton("Delete Product", this);
    reportButton = new QPushButton("Generate Report", this);

    layout->addWidget(productTable);
    layout->addWidget(addButton);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
    layout->addWidget(reportButton);

    auto *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addProduct);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editProduct);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteProduct);
    connect(reportButton, &QPushButton::clicked, this, &MainWindow::generateReport);

    dbManager.connectToDatabase();
}

MainWindow::~MainWindow() {
    dbManager.closeDatabase();
}

void MainWindow::addProduct() {
    QMessageBox::information(this, "Add", "Add Product clicked.");
}

void MainWindow::editProduct() {
    QMessageBox::information(this, "Edit", "Edit Product clicked.");
}

void MainWindow::deleteProduct() {
    QMessageBox::information(this, "Delete", "Delete Product clicked.");
}

void MainWindow::generateReport() {
    QMessageBox::information(this, "Report", "Generate Report clicked.");
}
