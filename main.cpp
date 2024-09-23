#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Main Menu");
    mainWindow.resize(320, 180);
    mainWindow.show();

    return app.exec();
}
