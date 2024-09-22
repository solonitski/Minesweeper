#include "game.h"
#include <QRandomGenerator>
#include <QMessageBox>

Game::Game(int rows, int cols, int mines, QWidget *parent)
    : ButtonGrid(rows, cols, parent), nRows(rows), nCols(cols), nMines(mines), firstClick(true), isEnd(false)
{
    initGame();

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
    isEnd = false;
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
    int idx = row * nCols + col;
    if (field[idx].isFlagged) {
        return;
    }

    if (firstClick) {
        firstClick = false;
        placeMines(row, col);
        calculateAdjacents();
    }

    if (field[idx].isRevealed)
        return;

    revealCell(row, col);

    // Проверка на выигрыш
    if (checkWinCondition()) {
        QMessageBox::information(nullptr, "Победа", "Вы выиграли!");
        lockField();
        isEnd = true;
    }
}

void Game::handleRightClick(int row, int col)
{
    int idx = row * nCols + col;
    if (field[idx].isRevealed)
        return;

    toggleFlag(row, col);

    // Проверка на выигрыш после установки флага
    if (checkWinCondition()) {
        QMessageBox::information(nullptr, "Победа", "Вы выиграли!");
        lockField();
        isEnd = true; // Устанавливаем флаг завершения игры
    }
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
        gameOver(row, col);  // Игра окончена
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
    SquareButton *btn = buttons.at(idx);

    if (!cell.isFlagged) {
        cell.isFlagged = true;
        btn->setText("🚩");
    } else {
        cell.isFlagged = false;
        btn->setText("");
    }
}

void Game::gameOver(int row, int col)
{
    if (isEnd) return; // Проверяем, что игра уже окончена, чтобы не выполнить код повторно.

    isEnd = true; // Устанавливаем флаг завершения игры

    // Отметить клетку, на которой произошел проигрыш
    int idx = row * nCols + col;
    SquareButton *btn = buttons.at(idx);
    btn->setStyleSheet("background-color: darkred;");
    btn->setText("💣");
    btn->setEnabled(false);

    // Раскрыть все ячейки
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            int idx = r * nCols + c;
            Cell& cell = field[idx];
            SquareButton *btn = buttons.at(idx);

            if (cell.hasMine) {
                if (!(r == row && c == col)) {
                    btn->setText("💣");
                }
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

    // Раскрыть все ячейки, которые не были ранее раскрыты
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            int idx = r * nCols + c;
            if (!field[idx].isRevealed && !(r == row && c == col)) {
                revealCell(r, c);
            }
        }
    }

    // Отобразить сообщение об окончании игры
    QMessageBox::information(nullptr, "Игра окончена", "Вы подорвались на мине!");
}


bool Game::checkWinCondition() {
    for (int i = 0; i < nRows * nCols; ++i) {
        if (field[i].hasMine) {
            if (!field[i].isFlagged) {
                return false;
            }
        } else {
            if (!field[i].isRevealed) {
                return false;
            }
        }
    }
    lockField();
    return true;
}

void Game::lockField()
{
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            int idx = r * nCols + c;
            buttons.at(idx)->setEnabled(false);
        }
    }
}
