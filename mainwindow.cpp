#include "mainwindow.h"
#include "game.h"
#include "settings.h"
#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), settings(10, 10, 10)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    QPushButton *startGameButton = new QPushButton("Start Game");
    QPushButton *settingsButton = new QPushButton("Settings");
    QPushButton *changeLanguageButton = new QPushButton("Change Language");

    buttons.push_back(startGameButton);
    buttons.push_back(settingsButton);
    buttons.push_back(changeLanguageButton);

    for(auto &button : buttons) {
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(button);
    }

    setCentralWidget(centralWidget);

    layout->setStretch(0, 1);
    layout->setStretch(1, 1);
    layout->setStretch(2, 1);

    QStringList args = QCoreApplication::arguments();
    if (args.size() > 1 && args[1] == "dbg") {
        debugMode = true; // Устанавливаем режим отладки
    }

    connect(startGameButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(settingsButton, &QPushButton::clicked, this, &MainWindow::openSettings);
    connect(changeLanguageButton, &QPushButton::clicked, this, &MainWindow::changeLanguage);
}

MainWindow::~MainWindow() = default;

void MainWindow::startGame()
{
    Game *game = new Game(settings, nullptr, debugMode);
    game->setWindowTitle("Сапёр");
    game->setMinimumHeight(10 * settings.getHeight() + 28);
    game->setMinimumWidth(10 * settings.getWidth());
    game->resize(30 * settings.getWidth(), 30 * settings.getHeight() + 42);
    game->show();

    this->hide();
}

void MainWindow::openSettings()
{
    SettingsDialog dialog(settings, this);
    if (dialog.exec() == QDialog::Accepted) {

    }
}

void MainWindow::changeLanguage()
{
    // В будущем здесь будет смена языка
}
