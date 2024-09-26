#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTranslator>
#include "settings.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(Settings &settings, QWidget *parent = nullptr);

private slots:
    void applySettings();

private:
    QLineEdit *widthLineEdit;
    QLineEdit *heightLineEdit;
    QLineEdit *minesLineEdit;
    Settings &settings;
};

#endif // SETTINGSDIALOG_H
