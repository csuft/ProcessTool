#include "qapplist.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QAppList win;
	win.setWindowIcon(QIcon(":/logo"));
	win.show();
	return app.exec();
}
