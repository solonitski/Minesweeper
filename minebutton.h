#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MineButton : public QPushButton {
    Q_OBJECT

public:
    MineButton(QWidget *parent = nullptr);

signals:
    void leftClicked();
    void rightClicked();
    void middleClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MINEBUTTON_H
