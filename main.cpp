#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Main Menu");
    mainWindow.resize(300, 300);
    mainWindow.show();

    return app.exec();
}
