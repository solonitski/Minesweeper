#include "buttongrid.h"
#include <QResizeEvent>
#include <QDebug>
#include <QStyle>
#include <QCoreApplication>

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

    centerButton = new SquareButton(this);
    centerButton->setStyleSheet("background-color: lightblue;");

    connect(centerButton, &SquareButton::leftClicked, this, [=]() {
        qDebug() << "Центральная кнопка: Левый клик";
    });

    rightButton = new SquareButton(this);
    rightButton->setStyleSheet("background-color: lightgreen;");

    connect(rightButton, &SquareButton::leftClicked, this, [=]() {
        qDebug() << "Правая кнопка: Левый клик";
    });

    setMinimumSize(minimumSizeHint());
}

void ButtonGrid::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    int gridWidth = width();
    int gridHeight = height();

    if (gridWidth <= 0 || gridHeight <= 0)
        return;

    const int minCellSize = 10;
    double scaleFactor = 1.2;
    double totalScale = nRows + scaleFactor;

    int cellWidth = gridWidth / nCols;
    int cellHeight = gridHeight / totalScale;

    int cellSize = qMax(minCellSize, qMin(cellWidth, cellHeight));

    int totalGridWidth = cellSize * nCols;
    int totalGridHeight = cellSize * nRows;

    int centerSize = static_cast<int>(cellSize * scaleFactor);
    int rightSize = centerSize;

    // Центрируем контент по высоте
    int totalContentHeight = std::max(centerSize, rightSize) + totalGridHeight;
    int yOffset = (gridHeight - totalContentHeight) / 2;
    yOffset = qMax(0, yOffset);

    // Центрируем контент по ширине
    int xOffset = (gridWidth - totalGridWidth) / 2;
    xOffset = qMax(0, xOffset);

    // Позиционируем центральную кнопку
    int centerX = xOffset + (totalGridWidth - centerSize) / 2;
    int centerY = yOffset;

    centerX = qMax(0, qMin(centerX, gridWidth - centerSize));
    centerY = qMax(0, qMin(centerY, gridHeight - centerSize - totalGridHeight));

    centerButton->setGeometry(centerX, centerY, centerSize, centerSize);
    centerButton->raise();

    // Позиционируем правую кнопку
    int rightX = centerX + centerSize; // Позиция справа от центральной кнопки
    int rightY = centerY;

    rightX = qMax(0, qMin(rightX, gridWidth - rightSize));
    rightY = qMax(0, qMin(rightY, gridHeight - rightSize - totalGridHeight));

    rightButton->setGeometry(rightX, rightY, rightSize, rightSize);
    rightButton->raise();

    // Позиционируем кнопки сетки
    int gridYStart = std::max(centerY + centerSize, rightY + rightSize);
    for (int idx = 0; idx < buttons.size(); ++idx) {
        int row = idx / nCols;
        int col = idx % nCols;
        int x = xOffset + col * cellSize;
        int y = gridYStart + row * cellSize;
        buttons[idx]->setGeometry(x, y, cellSize, cellSize);
    }
}

QSize ButtonGrid::minimumSizeHint() const {
    const int minButtonSize = 10;
    int totalWidth = minButtonSize * nCols + minButtonSize; // Дополнительное пространство для правой кнопки
    int totalHeight = minButtonSize * nRows + static_cast<int>(minButtonSize * 1.2);
    return QSize(totalWidth, totalHeight);
}

void ButtonGrid::buttonLeftClicked(int row, int col) {
    qDebug() << QString("Левый клик в ячейке (%1, %2)").arg(row).arg(col);
}

void ButtonGrid::buttonRightClicked(int row, int col) {
    qDebug() << QString("Правый клик в ячейке (%1, %2)").arg(row).arg(col);
}

void ButtonGrid::buttonMiddleClicked(int row, int col) {
    qDebug() << QString("Средний клик в ячейке (%1, %2)").arg(row).arg(col);
}
