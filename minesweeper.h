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

private slots:
    void buttonLeftClicked(int row, int col);
    void buttonRightClicked(int row, int col);
    void buttonMiddleClicked(int row, int col);

private:
    void createField();

    int numRows;
    int numCols;
    QGridLayout *gridLayout;
    QVector<MineButton*> buttons;
};

#endif // MINESWEEPER_H
