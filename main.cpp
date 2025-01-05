#include <QApplication>
#include "MainWindow.h"
#include "AuthDialog.h"
#include "DatabaseManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AuthDialog authDialog;
    if (authDialog.exec() == QDialog::Accepted) {
        DatabaseManager dbManager;
        dbManager.setConnectionDetails(
            authDialog.getHost(),
            authDialog.getPort(),
            authDialog.getUsername(),
            authDialog.getPassword()
        );
        dbManager.setDatabaseName(authDialog.getDatabaseName());

        if (dbManager.connectToDatabase()) {
            MainWindow mainWindow;
            mainWindow.showMaximized();
            return app.exec();
        } else {
            return 1; // Ошибка подключения к базе данных
        }
    }

    return 0; // Окно авторизации было закрыто
}
