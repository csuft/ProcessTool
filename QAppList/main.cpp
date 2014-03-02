/*
 * To compile the program, you should make sure whether the wchar_t is builtin type.
 * You can change the settings under: project property->C/C++->make wchar_t as builtin type
 */
#include "qapplist.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QFile file(":/uistyle");
	file.open(QFile::ReadOnly);
	qApp->setStyleSheet(file.readAll());
	file.close();

	QAppList win;
	win.setWindowIcon(QIcon(":/logo"));
	win.show();
	return app.exec();
}
