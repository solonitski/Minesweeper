#include "mainwindow.h"

MainWindow::MainWindow(bool dbgMode, QWidget *parent) :
	QMainWindow(parent), rows(10), columns(10), totalMines(10), gameOver(false), firstClick(true)
{
	std::srand(std::time(nullptr));

	centralWidget = new QWidget(this);
	mainLayout = new QVBoxLayout(centralWidget);

	tabWidget = new QTabWidget(this);

	gameWidget = new QWidget(this);
	gameLayout = new QVBoxLayout(gameWidget);

	gridLayout = new QGridLayout();
	gameLayout->addLayout(gridLayout);
	gameWidget->setLayout(gameLayout);

	settingsWidget = new SettingsWidget(this);
	connect(settingsWidget, &SettingsWidget::settingsChanged, this, &MainWindow::onSettingsChanged);

	tabWidget->addTab(gameWidget, "Game");
	tabWidget->addTab(settingsWidget, "Settings");

	BarLayout = new QVBoxLayout();

	BarLayout->addWidget(tabWidget);

	if (dbgMode)
	{
		dbgButton = new QPushButton("Peep");
		connect(dbgButton, &QPushButton::clicked, this, &MainWindow::toggleHiddenField);
		BarLayout->addWidget(dbgButton);
	}

	mainLayout->addLayout(BarLayout);

	setCentralWidget(centralWidget);

	createField(rows, columns);
}
MainWindow::~MainWindow() = default;

void MainWindow::createField(int rows, int columns)
{
	for (auto &row : buttons)
	{
		for (auto button : row)
		{
			gridLayout->removeWidget(button);
			delete button;
		}
		row.clear();
	}

	buttons.clear();

	buttons.resize(rows);
	mineField.resize(rows);
	revealed.resize(rows);
	flagged.resize(rows);
	for (int i = 0; i < rows; ++i)
	{
		buttons[i].resize(columns);
		mineField[i].resize(columns);
		revealed[i].resize(columns);
		flagged[i].resize(columns);

		for (int j = 0; j < columns; ++j)
		{
			button = new QPushButton(this);
			button->setMinimumSize(30, 30);
			button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
			buttons[i][j] = button;
			gridLayout->addWidget(button, i, j);
			connect(button, &QPushButton::clicked, this, &MainWindow::CellClicked);
			connect(button, &QPushButton::customContextMenuRequested, this, &MainWindow::RightClick);
			button->setContextMenuPolicy(Qt::CustomContextMenu);

			mineField[i][j] = 0;
			revealed[i][j] = false;
			flagged[i][j] = false;
		}
	}

	for (int i = 0; i < rows; ++i)
	{
		gridLayout->setRowStretch(i, 1);
	}
	for (int j = 0; j < columns; ++j)
	{
		gridLayout->setColumnStretch(j, 1);
	}
}

void MainWindow::placeMines(int totalMines, int firstRow, int firstCol)
{
	for (int i = 0; i < totalMines; ++i)
	{
		int row = std::rand() % rows;
		int col = std::rand() % columns;
		if ((row == firstRow && col == firstCol) || mineField[row][col] == -1)
		{
			--i;
		}
		else
		{
			mineField[row][col] = -1;

			for (int r = -1; r <= 1; ++r)
			{
				for (int c = -1; c <= 1; ++c)
				{
					int newRow = row + r;
					int newCol = col + c;
					if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns && mineField[newRow][newCol] != -1)
					{
						++mineField[newRow][newCol];
					}
				}
			}
		}
	}
}

void MainWindow::CellClicked()
{
	if (gameOver)
		return;

	clickedButton = qobject_cast< QPushButton * >(sender());

	if (!clickedButton)
		return;

	int row = -1;
	int col = -1;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			if (buttons[i][j] == clickedButton)
			{
				row = i;
				col = j;
				break;
			}
		}
		if (row != -1 && col != -1)
			break;
	}
	lastClickedRow = row;
	lastClickedCol = col;

	if (flagged[row][col])
		return;

	if (firstClick)
	{
		placeMines(totalMines, row, col);
		firstClick = false;
	}

	revealCell(row, col);
}

void MainWindow::RightClick()
{
	QPushButton *clickedButton = qobject_cast< QPushButton * >(sender());

	if (!clickedButton || gameOver)
		return;

	int row = -1;
	int col = -1;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			if (buttons[i][j] == clickedButton)
			{
				row = i;
				col = j;
				break;
			}
		}
		if (row != -1 && col != -1)
			break;
	}

	if (revealed[row][col])
		return;

	flagged[row][col] = !flagged[row][col];

	if (flagged[row][col])
	{
		clickedButton->setText("F");
		clickedButton->setStyleSheet("background-color: yellow;");
	}
	else
	{
		clickedButton->setText("");
		clickedButton->setStyleSheet("");
	}

	checkWin();
}

void MainWindow::revealCell(int row, int col)
{
	if (revealed[row][col] || flagged[row][col])
		return;

	revealed[row][col] = true;

	QPushButton *button = buttons[row][col];

	if (mineField[row][col] == -1)
	{
		button->setText("X");
		button->setStyleSheet("background-color: red;");
		message(false);
		return;
	}
	else if (mineField[row][col] > 0)
	{
		button->setText(QString::number(mineField[row][col]));
		button->setStyleSheet("background-color: lightgray;");
		checkWin();
		return;
	}
	else
	{
		button->setStyleSheet("background-color: lightgray;");

		for (int r = -1; r <= 1; ++r)
		{
			for (int c = -1; c <= 1; ++c)
			{
				int newRow = row + r;
				int newCol = col + c;
				if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns)
				{
					revealCell(newRow, newCol);
				}
			}
		}

		checkWin();
	}
}

void MainWindow::checkWin()
{
	bool allCellsOpen = true;
	bool allBombsFlagged = true;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			if (mineField[i][j] != -1 && !revealed[i][j])
			{
				allCellsOpen = false;
			}
			if (mineField[i][j] == -1 && !flagged[i][j])
			{
				allBombsFlagged = false;
			}
		}
	}

	if (allCellsOpen && allBombsFlagged)
	{
		message(true);
	}
}

void MainWindow::message(bool won)
{
	gameOver = true;
	QString message = won ? "Congratulations You won!" : "Game Over You hit a mine.";
	QMessageBox::information(this, "Game Over", message);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			if (mineField[i][j] == -1 && !flagged[i][j])
			{
				if (i == lastClickedRow && j == lastClickedCol)
				{
					buttons[i][j]->setText("X");
					buttons[i][j]->setStyleSheet("background-color: darkred;");
				}
				else
				{
					buttons[i][j]->setText("X");
					buttons[i][j]->setStyleSheet("background-color: red;");
				}
			}
		}
	}

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			if (!flagged[i][j])
			{
				buttons[i][j]->setEnabled(false);
			}
		}
	}
}

void MainWindow::onSettingsChanged()
{
	rows = settingsWidget->getRows();
	columns = settingsWidget->getColumns();
	totalMines = settingsWidget->getMines();

	gameOver = false;
	firstClick = true;

	createField(rows, columns);
}

void MainWindow::toggleHiddenField()
{
	static bool hiddenFieldsVisible = false;

	if (!hiddenFieldsVisible)
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				if (!revealed[i][j])
				{
					if (mineField[i][j] == -1)
					{
						buttons[i][j]->setText("X");
					}
					else
					{
						buttons[i][j]->setText(QString::number(mineField[i][j]));
					}
				}
			}
		}
		hiddenFieldsVisible = true;
	}
	else
	{
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				if (!revealed[i][j])
				{
					buttons[i][j]->setText("");
				}
			}
		}
		hiddenFieldsVisible = false;
	}
}
