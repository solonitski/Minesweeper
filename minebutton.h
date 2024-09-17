#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>

class MineButton : public QPushButton {
    Q_OBJECT

public:
    MineButton(QWidget *parent = nullptr, int x = 0, int y = 0, int size = 0);

    int getX();
    int getY();
    int getSize();
    void setMine(bool mine);
    bool hasMine() const;
    void setFlagged(bool flagged);
    bool isFlagged() const;
    void setNeighborMines(int count);
    int getNeighborMines() const;
    void setOpened(bool opened);
    bool isOpened() const;

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
    bool mine = false;
    bool flagged = false;
    bool opened = false;
    int neighborMines = 0;
};

#endif // MINEBUTTON_H
