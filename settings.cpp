#include "settings.h"

Settings::Settings(int width, int height, int mines, bool mode)
    : m_width(width), m_height(height), m_mines(mines), leftyMode(mode)
{
}

int Settings::getWidth() const
{
    return m_width;
}

int Settings::getHeight() const
{
    return m_height;
}

int Settings::getMines() const
{
    return m_mines;
}

bool Settings::getLeftyMode() const
{
    return leftyMode;
}

bool Settings::setWidth(int width)
{
    if (isValidFieldSize(width, m_height))
    {
        m_width = width;
        return true;
    }
    return false;
}

bool Settings::setHeight(int height)
{
    if (isValidFieldSize(m_width, height))
    {
        m_height = height;
        return true;
    }
    return false;
}

bool Settings::setMines(int mines)
{
    if (isValidMinesCount(mines))
    {
        m_mines = mines;
        return true;
    }
    return false;
}

bool Settings::setLeftyMode(bool mode) {
    leftyMode = mode;
    return true;
}

bool Settings::isValidFieldSize(int width, int height) const
{
    return width > 0 && height > 0;
}

bool Settings::isValidMinesCount(int mines) const
{
    return mines > 0 && mines < m_width * m_height;
}
