#include "MainWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupTabs();
    addGenerateReportMenu(); // Добавление меню
}

void MainWindow::addGenerateReportMenu() {
    QMenu *fileMenu = menuBar()->addMenu("ОТЧЕТЫ");
    QAction *generateReportAction = new QAction("CSV ОТЧЕТ", this);
    connect(generateReportAction, &QAction::triggered, this, &MainWindow::onGenerateReport);
    fileMenu->addAction(generateReportAction);
}

void MainWindow::onGenerateReport() {
    QString tableName;

    int currentIndex = tabWidget->currentIndex();
    if (currentIndex == 0) {
        tableName = "products";
    } else if (currentIndex == 1) {
        tableName = "categories";
    }  else if (currentIndex == 2) {
        tableName = "inventory_operations";
    } else {
        QMessageBox::warning(this, "Ошибка", "Неизвестная вкладка.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить CSV отчет", "", "CSV Файлы (*.csv)");
    if (!filePath.isEmpty()) {
        if (dbManager.generateCSVReport(tableName, filePath)) {
            QMessageBox::information(this, "УСПЕХ", "CSV отчет успешно сгенерирован.");
        } else {
            QMessageBox::warning(this, "ОШИБКА", "Ошибка при генерации CSV отчета.");
        }
    }
}


MainWindow::~MainWindow() {}

void MainWindow::setupTabs() {
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    productsTab = new QWidget();
    categoriesTab = new QWidget();
    operationsTab = new QWidget();

    tabWidget->addTab(productsTab, "Товары");
    tabWidget->addTab(categoriesTab, "Категории");
    tabWidget->addTab(operationsTab, "Операции");

    setupProductsUI(productsTab);
    setupCategoriesUI(categoriesTab);
    setupOperationsUi(operationsTab);
}

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
    layout->addWidget(new QLabel("Категория (ID):", parent));
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

    connect(editButton, &QPushButton::clicked, [this, table, nameEdit, skuEdit, categoryEdit, descriptionEdit, unitEdit, priceEdit, quantityEdit]() {
        int currentRow = table->currentRow();
        if (currentRow < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите строку для редактирования");
            return;
        }
        int productId = table->item(currentRow, 0)->text().toInt();
        if (!dbManager.editProduct(productId,
                                   nameEdit->text(), skuEdit->text(), categoryEdit->text().toInt(),
                                   descriptionEdit->text(), unitEdit->text(),
                                   priceEdit->text().toDouble(), quantityEdit->text().toInt())) {
            QMessageBox::critical(this, "Ошибка", "Не удалось редактировать товар");
        } else {
            updateProductsTable();
        }
    });

    connect(deleteButton, &QPushButton::clicked, [this, table]() {
        int currentRow = table->currentRow();
        if (currentRow < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите строку для удаления");
            return;
        }
        int productId = table->item(currentRow, 0)->text().toInt();
        if (!dbManager.deleteProduct(productId)) {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить товар");
        } else {
            updateProductsTable();
        }
    });

    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::updateProductsTable);

    updateProductsTable();
}

void MainWindow::setupCategoriesUI(QWidget *parent) {
    auto *layout = new QVBoxLayout(parent);

    auto *nameEdit = new QLineEdit(parent);
    auto *descriptionEdit = new QLineEdit(parent);

    layout->addWidget(new QLabel("Название:", parent));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Описание:", parent));
    layout->addWidget(descriptionEdit);

    auto *table = new QTableWidget(parent);
    table->setObjectName("categoriesTable");
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"ID", "Название", "Описание"});
    layout->addWidget(table);

    auto *addButton = new QPushButton("Добавить", parent);
    auto *editButton = new QPushButton("Редактировать", parent);
    auto *deleteButton = new QPushButton("Удалить", parent);
    auto *refreshButton = new QPushButton("Обновить", parent);

    layout->addWidget(addButton);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
    layout->addWidget(refreshButton);

    connect(addButton, &QPushButton::clicked, [this, nameEdit, descriptionEdit]() {
        if (!dbManager.addCategory(nameEdit->text(), descriptionEdit->text())) {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить категорию");
        } else {
            updateCategoriesTable();
        }
    });

    connect(editButton, &QPushButton::clicked, [this, table, nameEdit, descriptionEdit]() {
        int currentRow = table->currentRow();
        if (currentRow < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите строку для редактирования");
            return;
        }
        int categoryId = table->item(currentRow, 0)->text().toInt();
        if (!dbManager.editCategory(categoryId, nameEdit->text(), descriptionEdit->text())) {
            QMessageBox::critical(this, "Ошибка", "Не удалось редактировать категорию");
        } else {
            updateCategoriesTable();
        }
    });

    connect(deleteButton, &QPushButton::clicked, [this, table]() {
        int currentRow = table->currentRow();
        if (currentRow < 0) {
            QMessageBox::warning(this, "Ошибка", "Выберите строку для удаления");
            return;
        }
        int categoryId = table->item(currentRow, 0)->text().toInt();
        if (!dbManager.deleteCategory(categoryId)) {
            QMessageBox::critical(this, "Ошибка", "Не удалось удалить категорию");
        } else {
            updateCategoriesTable();
        }
    });

    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::updateCategoriesTable);

    updateCategoriesTable();
}

void MainWindow::updateProductsTable() {
    auto *table = findChild<QTableWidget *>("productsTable");
    if (!table) return;

    table->setRowCount(0);

    QSqlQuery products = dbManager.getProducts();
    while (products.next()) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(products.value("product_id").toString()));
        table->setItem(row, 1, new QTableWidgetItem(products.value("name").toString()));
        table->setItem(row, 2, new QTableWidgetItem(products.value("sku").toString()));
        table->setItem(row, 3, new QTableWidgetItem(products.value("category_id").toString()));
        table->setItem(row, 4, new QTableWidgetItem(products.value("description").toString()));
        table->setItem(row, 5, new QTableWidgetItem(products.value("unit").toString()));
        table->setItem(row, 6, new QTableWidgetItem(products.value("price").toString()));
        table->setItem(row, 7, new QTableWidgetItem(products.value("quantity").toString()));
    }
}

void MainWindow::updateCategoriesTable() {
    auto *table = findChild<QTableWidget *>("categoriesTable");
    if (!table) return;

    table->setRowCount(0);

    QSqlQuery categories = dbManager.getCategories();
    while (categories.next()) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(categories.value("category_id").toString()));
        table->setItem(row, 1, new QTableWidgetItem(categories.value("name").toString()));
        table->setItem(row, 2, new QTableWidgetItem(categories.value("description").toString()));
    }
}

void MainWindow::setupOperationsUi(QWidget *parent) {
    auto *layout = new QVBoxLayout(parent);
    auto *table = new QTableWidget(parent);

    auto *productIdEdit = new QLineEdit(parent);
    auto *warehouseIdEdit = new QLineEdit(parent);
    auto *operationTypeComboBox = new QComboBox(parent);
    auto *quantity = new QLineEdit(parent);
    auto *reason = new QLineEdit(parent);

    table->setObjectName("inventory_operations");
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({"ID", "ID продукта", "ID склада", "Тип операции", "Количество", "Причина", "Дата"});
    layout->addWidget(table);

    auto *refreshButton = new QPushButton("Обновить", parent);
    auto *addButton = new QPushButton("Добавить", parent);

    layout->addWidget(refreshButton);
    layout->addWidget(addButton);

    layout->addWidget(new QLabel("ID продукта:", parent));
    layout->addWidget(productIdEdit);
    layout->addWidget(new QLabel("ID склада:", parent));
    layout->addWidget(warehouseIdEdit);
    operationTypeComboBox->addItems({"поступление", "отгрузка", "списание"});
    layout->addWidget(new QLabel("Тип операции:", parent));
    layout->addWidget(operationTypeComboBox);
    layout->addWidget(new QLabel("Количество:", parent));
    layout->addWidget(quantity);
    layout->addWidget(new QLabel("Причина:", parent));
    layout->addWidget(reason);

    QString operationType = operationTypeComboBox->currentText();


    connect(addButton, &QPushButton::clicked, [this, productIdEdit, warehouseIdEdit, operationType, quantity, reason]() {
        if (!dbManager.addOperation(
                productIdEdit->text().toInt(),   // Передаем int напрямую
                warehouseIdEdit->text().toInt(), // Передаем int напрямую
                operationType,                  // Тип операции передается как строка
                quantity->text().toInt(),       // Передаем int напрямую
                reason->text()                  // Причина передается как QString
            )) {
            QMessageBox::critical(this, "Ошибка", "Не удалось добавить операцию");
        } else {
            updateProductsTable();
        }
    });

    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::updateCategoriesTable);

    updateCategoriesTable();
}


void MainWindow::updateOperationsTable() {
    auto *table = findChild<QTableWidget *>("inventory_operations");
    if (!table) return;

    table->setRowCount(0);

    QSqlQuery categories = dbManager.getCategories();
    while (categories.next()) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(categories.value("operation_id").toString()));
        table->setItem(row, 1, new QTableWidgetItem(categories.value("product_id").toString()));
        table->setItem(row, 2, new QTableWidgetItem(categories.value("warehouse_id").toString()));
        table->setItem(row, 2, new QTableWidgetItem(categories.value("operation_type").toString()));
        table->setItem(row, 2, new QTableWidgetItem(categories.value("quantity").toString()));
        table->setItem(row, 2, new QTableWidgetItem(categories.value("reason").toString()));
        table->setItem(row, 2, new QTableWidgetItem(categories.value("created_at").toString()));
    }
}