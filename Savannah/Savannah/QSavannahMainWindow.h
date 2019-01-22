#pragma once

#include <QtWidgets/QMainWindow>

//----------------------------------------------------------

class	QRenderWindow;
class	QRenderViewport;

//----------------------------------------------------------

class QSavannahMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QSavannahMainWindow(QWidget *parent = Q_NULLPTR);

	void				Setup();

private:
	QMenuBar			*m_MenuBar;
	QToolBar			*m_MainToolBar;
	QWidget				*m_CentralWidget;
	QStatusBar			*m_StatusBar;
	QRenderViewport		*m_RenderViewport;

	void				_CreateViewportPanel();
	void				_CreateControlPanel();

	void				_CreateRenderViewport(QWidget *parentWidget);
};

//----------------------------------------------------------
