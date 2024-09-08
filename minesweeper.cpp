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
    // Очистка существующих кнопок, если они есть.
    for (MineButton* btn : buttons) {
        gridLayout->removeWidget(btn);
        delete btn;
    }
    buttons.clear();

    // Пересоздаем вектор кнопок.
    buttons.resize(numRows * numCols);

    // Инициализируем каждую кнопку и добавляем в сетку.
    for (int i = 0; i < numRows; ++i) {
          for (int j = 0; j < numCols; ++j) {
              MineButton *btn = new MineButton(this, i, j, numRows * numCols);
              btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

              buttons[i * numCols + j] = btn;
              gridLayout->addWidget(btn, i, j);

              // Привязываем слоты на нажатие кнопок.
              connect(btn, &MineButton::leftClicked, [=]() {
                  buttonLeftClicked(i, j);
              });
              connect(btn, &MineButton::rightClicked, [=]() {
                  buttonRightClicked(i, j);
              });
              connect(btn, &MineButton::middleClicked, [=]() {
                  buttonMiddleClicked(i, j);
              });
          }
      }
}



// Проверки на нажатия клавиш. (потом использовать для поведений на определенной кнопке.)
void MineSweeper::buttonLeftClicked(int row, int col) {
    QMessageBox::information(this, "Left Button Clicked", QString("Left button at (%1, %2) clicked").arg(row).arg(col));
}

void MineSweeper::buttonRightClicked(int row, int col) {
    QMessageBox::information(this, "Right Button Clicked", QString("Right button at (%1, %2) clicked").arg(row).arg(col));
}

void MineSweeper::buttonMiddleClicked(int row, int col) {
    // не понятно почему не реагирует на нажатие скм (проверь у себя).
    QMessageBox::information(this, "Middle Button Clicked", QString("Middle button at (%1, %2) clicked").arg(row).arg(col));
}
