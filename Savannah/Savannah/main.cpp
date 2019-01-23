#include "stdafx.h"
#include "QSavannahMainWindow.h"
#include <QtWidgets/QApplication>

//----------------------------------------------------------

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);
	QApplication a(argc, argv);
	QSavannahMainWindow w;
	w.show();
	w.LaunchThreadGame();
	return a.exec();
}

//----------------------------------------------------------
