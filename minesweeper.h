#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include "minebutton.h"

class MineSweeper : public QWidget {
    Q_OBJECT

public:
    MineSweeper(QWidget *parent = nullptr);
    void setFieldSize(int rows, int cols);
    void setNumMines(int numMines);

private:
    QGridLayout *gridLayout;
    QVector<MineButton*> buttons;
    int numRows;
    int numCols;
    int totalMines;
    bool minesPlaced;
    bool gameOver;

    void createField();
    void placeMines(int initialRow, int initialCol);
    void calculateNeighborMines();
    void openCell(int row, int col);
    void revealMines();
    void checkWinCondition();
    void endGame(bool win);
    void deactivateField();
    void quickOpen(int row, int col);
    void markFlags();

private slots:
    void buttonLeftClicked(int row, int col);
    void buttonRightClicked(int row, int col);
    void buttonMiddleClicked(int row, int col);
};

#endif // MINESWEEPER_H
