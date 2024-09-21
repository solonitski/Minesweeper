#include <QApplication>
#include "game.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    int rows = 10;
    int cols = 10;
    int mines = 10;

    Game game(rows, cols, mines);
    game.setWindowTitle("Сапёр");
    game.setMinimumHeight(10);
    game.setMinimumWidth(10);
    game.resize(300, 300);
    game.show();

    return app.exec();
}
