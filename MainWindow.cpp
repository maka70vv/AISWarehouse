#include "MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupTabs();
}

MainWindow::~MainWindow() {}

void MainWindow::setupTabs() {
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    // Инициализация вкладок
    productsTab = new QWidget();
    operationsTab = new QWidget();
    usersTab = new QWidget();
    reportsTab = new QWidget();

    // Добавление вкладок
    tabWidget->addTab(productsTab, "Товары");
    tabWidget->addTab(operationsTab, "Операции");
    tabWidget->addTab(usersTab, "Пользователи");
    tabWidget->addTab(reportsTab, "Отчеты");

    // Настройка UI для каждой вкладки
    setupProductsUI(productsTab);
    setupOperationsUI(operationsTab);
    setupUsersUI(usersTab);
    setupReportsUI(reportsTab);
}

// ------------------ Товары ------------------

void MainWindow::setupProductsUI(QWidget *parent) {
    auto *layout = new QVBoxLayout(parent);

    auto *nameEdit = new QLineEdit(parent);
    auto *skuEdit = new QLineEdit(parent);
    auto *categoryEdit = new QLineEdit(parent);
    auto *descriptionEdit = new QLineEdit(parent);
    auto *unitEdit = new QLineEdit(parent);
    auto *priceEdit = new QLineEdit(parent);
    auto *quantityEdit = new QLineEdit(parent);

    layout->addWidget(new QLabel("Название:", parent));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Артикул:", parent));
    layout->addWidget(skuEdit);
    layout->addWidget(new QLabel("Категория:", parent));
    layout->addWidget(categoryEdit);
    layout->addWidget(new QLabel("Описание:", parent));
    layout->addWidget(descriptionEdit);
    layout->addWidget(new QLabel("Единица измерения:", parent));
    layout->addWidget(unitEdit);
    layout->addWidget(new QLabel("Цена:", parent));
    layout->addWidget(priceEdit);
    layout->addWidget(new QLabel("Количество:", parent));
    layout->addWidget(quantityEdit);

    auto *table = new QTableWidget(parent);
    table->setObjectName("productsTable");
    table->setColumnCount(8);
    table->setHorizontalHeaderLabels({"ID", "Название", "Артикул", "Категория", "Описание", "Единица", "Цена", "Количество"});
    layout->addWidget(table);

    auto *addButton = new QPushButton("Добавить", parent);
    auto *editButton = new QPushButton("Редактировать", parent);
    auto *deleteButton = new QPushButton("Удалить", parent);
    auto *refreshButton = new QPushButton("Обновить", parent);

    layout->addWidget(addButton);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
    layout->addWidget(refreshButton);

    connect(addButton, &QPushButton::clicked, [this, nameEdit, skuEdit, categoryEdit, descriptionEdit, unitEdit, priceEdit, quantityEdit]() {
        if (!dbManager.addProduct(
                nameEdit->text(), skuEdit->text(), categoryEdit->text().toInt(),
                descriptionEdit->text(), unitEdit->text(),
                priceEdit->text().toDouble(), quantityEdit->text().toInt())) {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить товар");
        } else {
            updateProductsTable();
        }
    });

    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::updateProductsTable);

    updateProductsTable();
}

void MainWindow::setupOperationsUI(QWidget *parent) {
    auto *layout = new QVBoxLayout(parent);
    layout->addWidget(new QLabel("Функционал для операций учета будет добавлен здесь", parent));
}

void MainWindow::setupUsersUI(QWidget *parent) {
    auto *layout = new QVBoxLayout(parent);
    layout->addWidget(new QLabel("Функционал для работы с пользователями будет добавлен здесь", parent));
}

void MainWindow::setupReportsUI(QWidget *parent) {
    auto *layout = new QVBoxLayout(parent);
    layout->addWidget(new QLabel("Функционал для отчетов будет добавлен здесь", parent));
}

void MainWindow::updateProductsTable() {
    auto *table = findChild<QTableWidget *>("productsTable");
    if (!table) return;

    table->setRowCount(0);

    QSqlQuery products = dbManager.getProducts();
    while (products.next()) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(products.value("id").toString()));
        table->setItem(row, 1, new QTableWidgetItem(products.value("name").toString()));
        table->setItem(row, 2, new QTableWidgetItem(products.value("sku").toString()));
        table->setItem(row, 3, new QTableWidgetItem(products.value("category_id").toString()));
        table->setItem(row, 4, new QTableWidgetItem(products.value("description").toString()));
        table->setItem(row, 5, new QTableWidgetItem(products.value("unit").toString()));
        table->setItem(row, 6, new QTableWidgetItem(products.value("price").toString()));
        table->setItem(row, 7, new QTableWidgetItem(products.value("quantity").toString()));
    }
}
