#include "buttongrid.h"
#include <QResizeEvent>
#include <algorithm>

ButtonGrid::ButtonGrid(int rows, int cols, QWidget *parent)
    : QWidget(parent), nRows(rows), nCols(cols) {
    for (int idx = 0; idx < nRows * nCols; ++idx) {
        SquareButton *btn = new SquareButton(this);
        buttons.push_back(btn);

        int row = idx / nCols;
        int col = idx % nCols;

        connect(btn, &SquareButton::leftClicked, this, [=]() {
            buttonLeftClicked(row, col);
        });
        connect(btn, &SquareButton::rightClicked, this, [=]() {
            buttonRightClicked(row, col);
        });
        connect(btn, &SquareButton::middleClicked, this, [=]() {
            buttonMiddleClicked(row, col);
        });
    }
}

void ButtonGrid::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    int gridWidth = width();
    int gridHeight = height();

    int cellWidth = gridWidth / nCols;
    int cellHeight = gridHeight / nRows;
    int cellSize = std::min(cellWidth, cellHeight);

    int totalGridWidth = cellSize * nCols;
    int totalGridHeight = cellSize * nRows;

    int xOffset = (gridWidth - totalGridWidth) / 2;
    int yOffset = (gridHeight - totalGridHeight) / 2;

    for (int idx = 0; idx < buttons.size(); ++idx) {
        int row = idx / nCols;
        int col = idx % nCols;
        int x = xOffset + col * cellSize;
        int y = yOffset + row * cellSize;
        buttons[idx]->setGeometry(x, y, cellSize, cellSize);
    }
}

void ButtonGrid::buttonLeftClicked(int row, int col) {
    qDebug("Left Clicked at (%d, %d)", row, col);
}

void ButtonGrid::buttonRightClicked(int row, int col) {
    qDebug("Right Clicked at (%d, %d)", row, col);
}

void ButtonGrid::buttonMiddleClicked(int row, int col) {
    qDebug("Middle Clicked at (%d, %d)", row, col);
}
