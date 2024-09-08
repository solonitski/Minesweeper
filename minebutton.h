#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MineButton : public QPushButton {
    Q_OBJECT

public:
    MineButton(QWidget *parent = nullptr, int x = 0, int y = 0, int size = 0);

signals:
    void leftClicked();
    void rightClicked();
    void middleClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    int x;
    int y;
    int size;

    int getX();
    int getY();
    int getSize();
};

#endif // MINEBUTTON_H
