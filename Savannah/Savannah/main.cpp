#include "stdafx.h"
#include "QSavannahMainWindow.h"
#include <QtWidgets/QApplication>

//----------------------------------------------------------

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);
	QApplication *a = new QApplication(argc, argv);
	QSavannahMainWindow *w = new QSavannahMainWindow();
	w->show();
	w->LaunchThreadGame();
	int result = a->exec();

	delete w;
	delete a;

	return result;
}

//----------------------------------------------------------
