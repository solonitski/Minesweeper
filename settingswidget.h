#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class SettingsWidget : public QWidget
{
	Q_OBJECT

  signals:
	void settingsChanged();

  public:
	explicit SettingsWidget(QWidget *parent = nullptr);

	void applySettings();

	int getRows() { return rowsSpinBox->value(); }
	int getColumns() { return columnsSpinBox->value(); }
	int getMines() { return minesSpinBox->value(); }

  private:
	QSpinBox *createSpinBox(int min, int max, int defaultValue, QWidget *parent);

	QSpinBox *rowsSpinBox;
	QSpinBox *columnsSpinBox;
	QSpinBox *minesSpinBox;
	QPushButton *startButton;
};

#endif	  // SETTINGSWIDGET_H
