#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT

public:
    // Конструктор с значениями по умолчанию
    Settings(int width = 10, int height = 10, int mines = 10);

    // Геттеры
    int getWidth() const;
    int getHeight() const;
    int getMines() const;

    // Сеттеры с проверкой
    bool setWidth(int width);
    bool setHeight(int height);
    bool setMines(int mines);

private:
    int m_width;
    int m_height;
    int m_mines;

    bool isValidFieldSize(int width, int height) const;
    bool isValidMinesCount(int mines) const;
};

#endif // SETTINGS_H
