#include "AuthDialog.h"

AuthDialog::AuthDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Авторизация и выбор базы данных");

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Хост:", this));
    hostEdit = new QLineEdit(this);
    hostEdit->setText("127.0.0.1"); // Дефолтное значение
    layout->addWidget(hostEdit);

    layout->addWidget(new QLabel("Порт:", this));
    portEdit = new QLineEdit(this);
    portEdit->setText("5432"); // Дефолтное значение
    layout->addWidget(portEdit);

    layout->addWidget(new QLabel("Имя пользователя:", this));
    usernameEdit = new QLineEdit(this);
    layout->addWidget(usernameEdit);

    layout->addWidget(new QLabel("Пароль:", this));
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    layout->addWidget(new QLabel("Имя базы данных:", this));
    databaseEdit = new QLineEdit(this);
    layout->addWidget(databaseEdit);

    okButton = new QPushButton("ОК", this);
    cancelButton = new QPushButton("Отмена", this);
    auto *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &AuthDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &AuthDialog::reject);
}

QString AuthDialog::getUsername() const {
    return usernameEdit->text();
}

QString AuthDialog::getPassword() const {
    return passwordEdit->text();
}

QString AuthDialog::getDatabaseName() const {
    return databaseEdit->text();
}

QString AuthDialog::getHost() const {
    return hostEdit->text();
}

int AuthDialog::getPort() const {
    return portEdit->text().toInt();
}
