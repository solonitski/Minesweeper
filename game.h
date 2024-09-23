#ifndef GAME_H
#define GAME_H

#include "buttongrid.h"
#include "settings.h"
#include <QVector>

class Game : public ButtonGrid
{
    Q_OBJECT

public:
    Game(Settings& settings, QWidget *parent = nullptr);

private:
    struct Cell {
        bool hasMine;
        bool isRevealed;
        bool isFlagged;
        int adjacentMines;
    };

    int nRows;
    int nCols;
    int nMines;
    bool firstClick;
    bool isEnd;
    QPoint windowPosition;
    QVector<Cell> field;

    void initGame();
    void placeMines(int initialRow, int initialCol);
    void calculateAdjacents();
    void handleLeftClick(int row, int col);
    void handleRightClick(int row, int col);
    void revealCell(int row, int col);
    void revealAdjacentCells(int row, int col);
    void toggleFlag(int row, int col);
    void gameOver(int row, int col);
    bool checkWinCondition();
    void lockField();
    void resetGame();
    void resetGameSlot();
    void openSettingsDialog();

    Settings& settings; // Хранение настроек
};

#endif // GAME_H
