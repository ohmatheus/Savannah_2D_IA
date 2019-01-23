#pragma once

#include <QMainWindow>
#include <QThread>

//----------------------------------------------------------

class	QRenderWindow;
class	QRenderViewport;

//----------------------------------------------------------

class QSavannahMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QSavannahMainWindow(QWidget *parent = Q_NULLPTR);

	virtual ~QSavannahMainWindow();


	void				Setup();
	void				StartGameThread();

signals:
	void				LaunchThreadGame();

private:
	QMenuBar			*m_MenuBar;
	QToolBar			*m_MainToolBar;
	QWidget				*m_CentralWidget;
	QStatusBar			*m_StatusBar;
	QRenderViewport		*m_RenderViewport;
	QThread				m_GameThread;
	QRenderWindow		*m_RenderWindow;

	void				_CreateViewportPanel();
	void				_CreateControlPanel();

	void				_CreateRenderViewport(QWidget *parentWidget);
	void				_GameLoop();
};

//----------------------------------------------------------
