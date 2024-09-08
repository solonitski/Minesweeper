#include "minesweeper.h"
#include <QMessageBox>

MineSweeper::MineSweeper(QWidget *parent) : QWidget(parent), numRows(0), numCols(0) {
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(1);
    setLayout(gridLayout);
    setWindowTitle("MineSweeper");
}

void MineSweeper::setFieldSize(int rows, int cols) {
    numRows = rows;
    numCols = cols;
    createField();
}

void MineSweeper::createField() {
    // Очистка существующих кнопок, если они есть
    for (QPushButton* btn : buttons) {
        gridLayout->removeWidget(btn);
        delete btn;
    }
    buttons.clear();

    // Создаем вектор кнопок
    buttons.resize(numRows * numCols);

    // Инициализируем каждую кнопку и добавляем в сетку
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            QPushButton *btn = new QPushButton(this);
            btn->setFixedSize(40, 40); // Задаем размер кнопки
            buttons[i * numCols + j] = btn;
            gridLayout->addWidget(btn, i, j);

            // Привязываем слот на нажатие кнопки
            connect(btn, &QPushButton::clicked, [=]() {
                buttonClicked(i, j);
            });
        }
    }
    resize(40 * numCols + 20, 40 * numRows + 20);
}

void MineSweeper::buttonClicked(int row, int col) {
    QMessageBox::information(this, "Button Clicked", QString("Button at (%1, %2) clicked").arg(row).arg(col));
}
