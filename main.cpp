#include <QApplication>
#include "minesweeper.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MineSweeper w;
    w.setFieldSize(10, 10);  // Установка размера поля
    w.setNumMines(10);  // Установка фиксированного числа мин
    w.show();

    return a.exec();
}
