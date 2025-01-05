#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class AuthDialog : public QDialog {
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;
    QString getDatabaseName() const;
    QString getHost() const;
    int getPort() const;

private:
    QLineEdit *hostEdit;
    QLineEdit *portEdit;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *databaseEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif
