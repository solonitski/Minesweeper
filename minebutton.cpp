#include "minebutton.h"
#include <QMouseEvent>
#include <QResizeEvent>
#include <QDebug>
#include <QtMath>

MineButton::MineButton(QWidget *parent, int x, int y, int size) : QPushButton(parent) {
    this->x = x;
    this->y = y;
    this->size = size;
}

int MineButton::getX() {
    return x;
}

int MineButton::getY() {
    return y;
}

int MineButton::getSize() {
    return size;
}

void MineButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit leftClicked();
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked();
    } else if (event->button() == Qt::MiddleButton) {
        emit middleClicked();
    }
    QPushButton::mousePressEvent(event);
}

void MineButton::resizeEvent(QResizeEvent *event)  {
    QPushButton::resizeEvent(event);
    //чтобы найти размер одного квадратика просто находим площадь окна(до этого вычислив какой процент занимает верхняя строчка),
    //с коэфом 0.5 норм работает, но нужно проапгрейдить формулу, а именно как-то правильно отрегулировать ширину
    float size = parentWidget()->size().width() * parentWidget()->size().height() * 0.5;
    size /= getSize();
    size = qSqrt(size);
    setGeometry(getX() * size, getY() * size, size, size);
}


