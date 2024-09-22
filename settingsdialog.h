#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "settings.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(Settings &settings, QWidget *parent = nullptr);

private slots:
    void applySettings();

private:
    QLineEdit *widthLineEdit;
    QLineEdit *heightLineEdit;
    QLineEdit *minesLineEdit;

    Settings &settings; // Ссылка на оригинальные настройки
};

#endif // SETTINGSDIALOG_H
