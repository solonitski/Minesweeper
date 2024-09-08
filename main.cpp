#include <QApplication>
#include "minesweeper.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MineSweeper window;
    window.setFieldSize(10, 10);
    window.show();

    return app.exec();
}
