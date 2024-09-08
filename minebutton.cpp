#include "minebutton.h"

MineButton::MineButton(QWidget *parent) : QPushButton(parent) {
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
