#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settingswidget.h"

#include <QGridLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QVector>
#include <cstdlib>
#include <ctime>

class MainWindow : public QMainWindow
{
	Q_OBJECT

  public:
	explicit MainWindow(bool dbgMode, QWidget *parent = nullptr);
	~MainWindow();

  private:
	void CellClicked();
	void RightClick();
	void onSettingsChanged();
	void toggleHiddenField();

	void createField(int rows, int columns);
	void placeMines(int totalMines, int firstRow, int firstCol);
	void revealCell(int row, int col);
	void checkWin();
	void message(bool won);

	int rows;
	int columns;
	int totalMines;
	bool gameOver;
	bool firstClick;
	int lastClickedRow;
	int lastClickedCol;

	QGridLayout *gridLayout;
	QTabWidget *tabWidget;
	SettingsWidget *settingsWidget;
	QPushButton *clickedButton;
	QPushButton *dbgButton;
	QWidget *gameWidget;
	QWidget *centralWidget;
	QVBoxLayout *gameLayout;
	QVBoxLayout *BarLayout;
	QVBoxLayout *mainLayout;
	QPushButton *button;

	QVector< QVector< QPushButton * > > buttons;
	QVector< QVector< int > > mineField;
	QVector< QVector< bool > > revealed;
	QVector< QVector< bool > > flagged;
};

#endif	  // MAINWINDOW_H
