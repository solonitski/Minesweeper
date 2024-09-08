#include "mainwindow.h"

#include <QApplication>
#include <string>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	bool dbgMode = false;

	if (argc > 1 && std::string(argv[1]) == "dbg")
	{
		dbgMode = true;
	}

	MainWindow w(dbgMode);
	w.show();
	return a.exec();
}
