#ifndef GAME_H
#define GAME_H

#include "buttongrid.h"
#include <QVector>
#include <QObject>
#include <QMessageBox>

struct Cell {
    bool hasMine;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;
};

class Game : public ButtonGrid {
    Q_OBJECT

public:
    Game(int rows, int cols, int mines, QWidget *parent = nullptr);

private:
    int nRows;
    int nCols;
    int nMines;
    QVector<Cell> field;
    bool firstClick;       // Для отслеживания первого клика
    void initGame();
    void placeMines(int initialRow, int initialCol);  // Обновленная функция
    void calculateAdjacents();
    void revealCell(int row, int col);
    void revealAdjacentCells(int row, int col);
    void toggleFlag(int row, int col);
    void gameOver(int row, int col);

private slots:
    void handleLeftClick(int row, int col);
    void handleRightClick(int row, int col);
};

#endif // GAME_H
