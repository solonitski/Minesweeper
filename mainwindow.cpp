#include "mainwindow.h"
#include "game.h"
#include "settings.h"
#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), settings(10, 10, 10) // Инициализируем настройки значениями по умолчанию
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(0); // Убираем отступы между кнопками, если необходимо
    layout->setContentsMargins(0, 0, 0, 0); // Убираем внешние отступы, если необходимо

    // Создаём кнопки без передачи this в качестве родителя,
    // так как они уже будут добавлены в layout, который установит им правильного родителя
    QPushButton *startGameButton = new QPushButton("Start Game");
    QPushButton *settingsButton = new QPushButton("Settings");
    QPushButton *changeLanguageButton = new QPushButton("Change Language");

    buttons.push_back(startGameButton);
    buttons.push_back(settingsButton);
    buttons.push_back(changeLanguageButton);

    // Устанавливаем политику размера для кнопок, чтобы они расширялись
    for(auto &button : buttons) {
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(button);
    }

    setCentralWidget(centralWidget);

    // Устанавливаем растяжку для равномерного распределения пространства
    layout->setStretch(0, 1);
    layout->setStretch(1, 1);
    layout->setStretch(2, 1);

    // Подключаем сигналы

    connect(startGameButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::openSettings);
    connect(changeLanguageButton, &QPushButton::clicked, this, &MainWindow::changeLanguage);
}

MainWindow::~MainWindow() = default;

void MainWindow::startGame()
{
    Game *game = new Game(settings.getWidth(), settings.getHeight(), settings.getMines());
    game->setWindowTitle("Сапёр");
    game->setMinimumHeight(10);
    game->setMinimumWidth(10);
    game->resize(300, 300);
    game->show();

    // Скрываем главное окно
    this->hide();
}

void MainWindow::openSettings()
{
    SettingsDialog dialog(settings, this);
    if (dialog.exec() == QDialog::Accepted)
    {
        // Новые настройки успешно применены
        qDebug() << "Settings updated in main window!";
    }
}

void MainWindow::changeLanguage()
{
    // В будущем здесь будет смена языка
}
