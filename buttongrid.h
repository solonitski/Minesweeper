#ifndef BUTTONGRID_H
#define BUTTONGRID_H

#include "squarebutton.h"
#include <QWidget>
#include <QVector>

class ButtonGrid : public QWidget {
    Q_OBJECT

public:
    ButtonGrid(int rows, int cols, QWidget *parent = nullptr);

    int getRowCount() const { return nRows; }
    int getColCount() const { return nCols; }
    const QVector<SquareButton*>& getButtons() const { return buttons; }

protected:
    void resizeEvent(QResizeEvent *event) override;

    int nRows;
    int nCols;
    QVector<SquareButton*> buttons;

private slots:
    virtual void buttonLeftClicked(int row, int col);
    virtual void buttonRightClicked(int row, int col);
    virtual void buttonMiddleClicked(int row, int col);
};

#endif // BUTTONGRID_H
