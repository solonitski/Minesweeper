#include "game.h"
#include <QRandomGenerator>
#include <QMessageBox>

Game::Game(int rows, int cols, int mines, QWidget *parent)
    : ButtonGrid(rows, cols, parent), nRows(rows), nCols(cols), nMines(mines), firstClick(true)
{
    // Инициализируем игровое поле
    initGame();

    // Подключаем сигналы от кнопок к слотам игры
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            int idx = row * nCols + col;
            SquareButton *btn = buttons.at(idx);

            connect(btn, &SquareButton::leftClicked, this, [=]() {
                handleLeftClick(row, col);
            });
            connect(btn, &SquareButton::rightClicked, this, [=]() {
                handleRightClick(row, col);
            });
        }
    }
}

void Game::initGame()
{
    field.resize(nRows * nCols);
    for (int i = 0; i < nRows * nCols; ++i) {
        field[i] = {false, false, false, 0};
    }
}

void Game::placeMines(int initialRow, int initialCol)
{
    int minesPlaced = 0;
    while (minesPlaced < nMines) {
        int row = QRandomGenerator::global()->bounded(nRows);
        int col = QRandomGenerator::global()->bounded(nCols);
        int idx = row * nCols + col;

        if ((row == initialRow && col == initialCol) || field[idx].hasMine)
            continue;

        field[idx].hasMine = true;
        ++minesPlaced;
    }
}

void Game::calculateAdjacents()
{
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            int idx = row * nCols + col;
            if (field[idx].hasMine) {
                field[idx].adjacentMines = -1;
                continue;
            }

            int mineCount = 0;
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    int newRow = row + dr;
                    int newCol = col + dc;
                    if (newRow >= 0 && newRow < nRows &&
                        newCol >= 0 && newCol < nCols &&
                        field[newRow * nCols + newCol].hasMine) {
                        ++mineCount;
                    }
                }
            }
            field[idx].adjacentMines = mineCount;
        }
    }
}

void Game::handleLeftClick(int row, int col)
{
    if (firstClick) {
        firstClick = false;
        placeMines(row, col);
        calculateAdjacents();
    }

    int idx = row * nCols + col;
    if (field[idx].isRevealed || field[idx].isFlagged)
        return;

    revealCell(row, col);

    int cellsLeft = 0;
    for (const auto& cell : field) {
        if (!cell.isRevealed && !cell.hasMine) {
            ++cellsLeft;
        }
    }

    if (cellsLeft == 0) {
        QMessageBox::information(nullptr, "Победа", "Вы выиграли!");
    }
}

void Game::handleRightClick(int row, int col)
{
    int idx = row * nCols + col;
    if (field[idx].isRevealed)
        return;

    toggleFlag(row, col);
}

void Game::revealCell(int row, int col)
{
    if (row < 0 || row >= nRows || col < 0 || col >= nCols)
        return;

    int idx = row * nCols + col;
    Cell& cell = field[idx];

    if (cell.isRevealed || cell.isFlagged)
        return;

    cell.isRevealed = true;
    SquareButton *btn = buttons.at(idx);

    if (cell.hasMine) {
        btn->setText("💣");
        btn->setStyleSheet("background-color: red;");
        gameOver(row, col);  // Проигрыш
    } else if (cell.adjacentMines > 0) {
        btn->setText(QString::number(cell.adjacentMines));
        btn->setEnabled(false);
    } else {
        btn->setEnabled(false);
        revealAdjacentCells(row, col);
    }
}

void Game::revealAdjacentCells(int row, int col)
{
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int newRow = row + dr;
            int newCol = col + dc;
            if (newRow >= 0 && newRow < nRows &&
                newCol >= 0 && newCol < nCols) {
                int idx = newRow * nCols + newCol;
                if (!field[idx].isRevealed) {
                    revealCell(newRow, newCol);
                }
            }
        }
    }
}

void Game::toggleFlag(int row, int col)
{
    int idx = row * nCols + col;
    Cell& cell = field[idx];
    cell.isFlagged = !cell.isFlagged;

    SquareButton *btn = buttons.at(idx);

    if (cell.isFlagged) {
        btn->setText("🚩");
    } else {
        btn->setText("");
    }
}

void Game::gameOver(int row, int col)
{
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            int idx = r * nCols + c;
            Cell& cell = field[idx];
            SquareButton *btn = buttons.at(idx);

            if (cell.hasMine && !(r == row && c == col)) {
                btn->setText("💣");
            }

            if (cell.isFlagged) {
                if (cell.hasMine) {
                    btn->setStyleSheet("background-color: lightgreen;");
                    btn->setText("🚩");
                } else {
                    btn->setStyleSheet("background-color: lightcoral;");
                }
            }

            btn->setEnabled(false);
        }
    }

    // Отметить клетку, на которой произошел проигрыш
    int idx = row * nCols + col;
    SquareButton *btn = buttons.at(idx);
    btn->setStyleSheet("background-color: darkred;");

    QMessageBox::information(nullptr, "Игра окончена", "Вы подорвались на мине!");
}
