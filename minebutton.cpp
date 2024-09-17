#include "minebutton.h"
#include <QMouseEvent>
#include <QResizeEvent>
#include <QDebug>
#include <QtMath>

MineButton::MineButton(QWidget *parent, int x, int y, int size)
    : QPushButton(parent), x(x), y(y), size(size) {}

int MineButton::getX() {
    return x;
}

int MineButton::getY() {
    return y;
}

int MineButton::getSize() {
    return size;
}

void MineButton::setMine(bool mine) {
    this->mine = mine;
}

bool MineButton::hasMine() const {
    return mine;
}

void MineButton::setFlagged(bool flagged) {
    this->flagged = flagged;
}

bool MineButton::isFlagged() const {
    return flagged;
}

void MineButton::setNeighborMines(int count) {
    neighborMines = count;
}

int MineButton::getNeighborMines() const {
    return neighborMines;
}

void MineButton::setOpened(bool opened) {
    this->opened = opened;
}

bool MineButton::isOpened() const {
    return opened;
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
    float size = parentWidget()->size().width() * parentWidget()->size().height() * 0.5;
    size /= getSize();
    size = qSqrt(size);
    setGeometry(getX() * size, getY() * size, size, size);
}
