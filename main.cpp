#include <QApplication>
#include <QTranslator>
#include "mainwindow.h"
#include "settings.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Settings settings;

    MainWindow mainWindow(settings);
    mainWindow.resize(320, 180);
    mainWindow.show();
    mainWindow.show();

    return app.exec();
}
