#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVector>

class MineSweeper : public QWidget {
    Q_OBJECT

public:
    MineSweeper(QWidget *parent = nullptr);
    void setFieldSize(int rows, int cols);

private slots:
    void buttonClicked(int row, int col);

private:
    void createField();

    int numRows;
    int numCols;
    QGridLayout *gridLayout;
    QVector<QPushButton*> buttons;
};

#endif // MINESWEEPER_H
