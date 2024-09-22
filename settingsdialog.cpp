#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox> // Добавляем для отображения сообщений об ошибках
#include <QDebug>

SettingsDialog::SettingsDialog(Settings &settings, QWidget *parent)
    : QDialog(parent), settings(settings)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создаём элементы ввода данных
    widthLineEdit = new QLineEdit(QString::number(settings.getWidth()), this);
    heightLineEdit = new QLineEdit(QString::number(settings.getHeight()), this);
    minesLineEdit = new QLineEdit(QString::number(settings.getMines()), this);

    // Добавляем лейблы и поля ввода для каждой настройки
    layout->addWidget(new QLabel("Width:"));
    layout->addWidget(widthLineEdit);

    layout->addWidget(new QLabel("Height:"));
    layout->addWidget(heightLineEdit);

    layout->addWidget(new QLabel("Mines:"));
    layout->addWidget(minesLineEdit);

    // Кнопка для применения изменённых настроек
    QPushButton *applyButton = new QPushButton("Apply", this);
    layout->addWidget(applyButton);

    // Подключаем сигнал кнопки к слоту
    connect(applyButton, &QPushButton::clicked, this, &SettingsDialog::applySettings);
}

void SettingsDialog::applySettings()
{
    int newWidth = widthLineEdit->text().toInt();
    int newHeight = heightLineEdit->text().toInt();
    int newMines = minesLineEdit->text().toInt();

    // Проверяем корректность введенных данных
    bool valid = true;
    QString errorMsg;

    if (!settings.setWidth(newWidth)) {
        valid = false;
        errorMsg += "Invalid width value.\n";
    }
    if (!settings.setHeight(newHeight)) {
        valid = false;
        errorMsg += "Invalid height value.\n";
    }
    if (!settings.setMines(newMines)) {
        valid = false;
        errorMsg += "Invalid mines value.\n";
    }

    if (valid) {
        qDebug() << "New settings applied!";
        accept(); // Закроем диалог, если всё успешно
    } else {
        qDebug() << "Invalid settings!";
        QMessageBox::warning(this, "Invalid input", errorMsg); // Выводим окно с сообщением об ошибке
    }
}
