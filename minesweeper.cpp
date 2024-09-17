#include "minesweeper.h"
#include <QMessageBox>
#include <QRandomGenerator>

MineSweeper::MineSweeper(QWidget *parent)
    : QWidget(parent), numRows(0), numCols(0), totalMines(0), minesPlaced(false), gameOver(false) {
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(1);
    setLayout(gridLayout);
    setWindowTitle("MineSweeper");
}

void MineSweeper::setFieldSize(int rows, int cols) {
    numRows = rows;
    numCols = cols;
    minesPlaced = false;
    gameOver = false;
    createField();
}

void MineSweeper::setNumMines(int numMines) {
    totalMines = numMines;
}

void MineSweeper::createField() {
    for (MineButton* btn : buttons) {
        gridLayout->removeWidget(btn);
        delete btn;
    }
    buttons.clear();
    buttons.resize(numRows * numCols);

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            MineButton *btn = new MineButton(this, i, j, numRows * numCols);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttons[i * numCols + j] = btn;
            gridLayout->addWidget(btn, i, j);
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

void MineSweeper::placeMines(int initialRow, int initialCol) {
    int placedMines = 0;
    while (placedMines < totalMines) {
        int row = QRandomGenerator::global()->bounded(numRows);
        int col = QRandomGenerator::global()->bounded(numCols);
        int index = row * numCols + col;

        if ((row == initialRow && col == initialCol) || buttons[index]->hasMine()) {
            continue;
        }
        buttons[index]->setMine(true);
        placedMines++;
    }
    minesPlaced = true;
    calculateNeighborMines();
}

void MineSweeper::calculateNeighborMines() {
    const QVector<QPair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},         { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (buttons[i * numCols + j]->hasMine()) {
                continue;
            }

            int count = 0;
            for (const auto& dir : directions) {
                int newRow = i + dir.first;
                int newCol = j + dir.second;

                if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
                    if (buttons[newRow * numCols + newCol]->hasMine()) {
                        count++;
                    }
                }
            }
            buttons[i * numCols + j]->setNeighborMines(count);
        }
    }
}

void MineSweeper::openCell(int row, int col) {
    int index = row * numCols + col;
    if (buttons[index]->isOpened() || buttons[index]->hasMine() || buttons[index]->isFlagged()) {
        return;
    }

    buttons[index]->setOpened(true);
    buttons[index]->setEnabled(false);

    if (buttons[index]->getNeighborMines() > 0) {
        buttons[index]->setText(QString::number(buttons[index]->getNeighborMines()));
    } else {
        const QVector<QPair<int, int>> directions = {
            {-1, -1}, {-1, 0}, {-1, 1},
            { 0, -1},         { 0, 1},
            { 1, -1}, { 1, 0}, { 1, 1}
        };

        for (const auto& dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;

            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
                openCell(newRow, newCol);
            }
        }
    }
}

void MineSweeper::revealMines() {
    for (MineButton* btn : buttons) {
        if (btn->hasMine()) {
            btn->setText("M");
            btn->setStyleSheet("QPushButton { color: red; }");
        }
    }
}

void MineSweeper::markFlags() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            int index = i * numCols + j;
            if (buttons[index]->isFlagged()) {
                if (buttons[index]->hasMine()) {
                    buttons[index]->setStyleSheet("QPushButton { background-color: lightgreen; color: black; }");
                } else {
                    buttons[index]->setStyleSheet("QPushButton { background-color: red; color: white; }");
                }
            }
        }
    }
}


void MineSweeper::checkWinCondition() {
    for (MineButton* btn : buttons) {
        if (!btn->hasMine() && !btn->isOpened()) {
            return;
        }
    }
    endGame(true);
}

void MineSweeper::endGame(bool win) {
    gameOver = true;
    deactivateField();

    if (win) {
        markFlags();
        QMessageBox::information(this, "Win", "You win!");
    } else {
        revealMines();
        markFlags();
        QMessageBox::information(this, "Game Over", "You clicked on a mine!");
    }
}


void MineSweeper::deactivateField() {
    for (MineButton* btn : buttons) {
        btn->setEnabled(false);
    }
}

void MineSweeper::quickOpen(int row, int col) {
    int index = row * numCols + col;

    // Если клетка уже открыта или имеет мину, ничего не делаем
    if (!buttons[index]->isOpened() || buttons[index]->hasMine()) {
        return;
    }

    // Направления для проверки соседних клеток
    QVector<QPair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        { 0, -1},         { 0, 1},
        { 1, -1}, { 1, 0}, { 1, 1}
    };

    int flaggedMinesCount = 0;
    int totalMinesAround = buttons[index]->getNeighborMines();
    QVector<QPair<int, int>> cellsToOpen;

    // Подсчитываем количество флажков вокруг и собираем закрытые клетки
    for (const auto& dir : directions) {
        int newRow = row + dir.first;
        int newCol = col + dir.second;
        if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
            int neighborIndex = newRow * numCols + newCol;
            if (buttons[neighborIndex]->hasMine() && buttons[neighborIndex]->isFlagged()) {
                flaggedMinesCount++;
            }
            if (!buttons[neighborIndex]->isOpened() && !buttons[neighborIndex]->isFlagged()) {
                cellsToOpen.append(qMakePair(newRow, newCol));
            }
        }
    }

    // Если все мины вокруг отмечены флагами, открываем все закрытые клетки вокруг
    if (flaggedMinesCount == totalMinesAround) {
        for (const auto& cell : cellsToOpen) {
            openCell(cell.first, cell.second);
        }
    } else {
        // Подсвечиваем все закрытые клетки вокруг
        for (const auto& cell : cellsToOpen) {
            int neighborIndex = cell.first * numCols + cell.second;
            buttons[neighborIndex]->setStyleSheet("QPushButton { background-color: lightblue; }");
        }
    }
}

void MineSweeper::buttonLeftClicked(int row, int col) {
    if (gameOver) return;

    int index = row * numCols + col;
    if (buttons[index]->isFlagged()) {
        return;
    }

    if (!minesPlaced) {
        placeMines(row, col);
    }

    if (buttons[index]->hasMine()) {
        endGame(false);
    } else {
        openCell(row, col);
        checkWinCondition();
    }
}

void MineSweeper::buttonRightClicked(int row, int col) {
    if (gameOver) return;

    int index = row * numCols + col;
    if (!buttons[index]->isOpened()) {
        buttons[index]->setFlagged(!buttons[index]->isFlagged());
        if (buttons[index]->isFlagged()) {
            buttons[index]->setStyleSheet("QPushButton { background-color: yellow; }");
        } else {
            buttons[index]->setStyleSheet("");
        }
    }
}

void MineSweeper::buttonMiddleClicked(int row, int col) {
    if (gameOver) return;

    quickOpen(row, col);
}
