#include "settingswidget.h"

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget(parent)
{
	QFormLayout* formLayout = new QFormLayout(this);

	rowsSpinBox = createSpinBox(2, 20, 10, this);
	columnsSpinBox = createSpinBox(2, 20, 10, this);
	minesSpinBox = createSpinBox(1, 20, 10, this);

	formLayout->addRow(new QLabel("Rows:"), rowsSpinBox);
	formLayout->addRow(new QLabel("Columns:"), columnsSpinBox);
	formLayout->addRow(new QLabel("Mines:"), minesSpinBox);

	startButton = new QPushButton("Start new game", this);
	formLayout->addRow(startButton);
	connect(startButton, &QPushButton::clicked, this, &SettingsWidget::applySettings);
}

void SettingsWidget::applySettings()
{
	emit settingsChanged();
}

QSpinBox* SettingsWidget::createSpinBox(int min, int max, int defaultValue, QWidget* parent)
{
	QSpinBox* spinBox = new QSpinBox(parent);
	spinBox->setRange(min, max);
	spinBox->setValue(defaultValue);
	return spinBox;
}
