#ifndef LANGUAGEDIALOG_H
#define LANGUAGEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "settings.h"

class LanguageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LanguageDialog(Settings &settings, QWidget *parent = nullptr);
    Language selectedLanguage() const;
    void acceptSelection();

private:
    QComboBox *languageComboBox;
    Settings &settings;
};

#endif // LANGUAGEDIALOG_H
