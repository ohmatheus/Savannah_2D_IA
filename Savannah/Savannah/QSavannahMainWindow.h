#pragma once

#include <QMainWindow>
#include <QThread>

//----------------------------------------------------------

class	QPushButton;
class	QRenderWindow;
class	QRenderViewport;
class	QWorkerObject;
class	Game;
class	QSceneControllerW;
class	QSlider;

//----------------------------------------------------------

class QSavannahMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	QSavannahMainWindow(QWidget *parent = Q_NULLPTR);

	virtual ~QSavannahMainWindow();

	void				Setup();
	void				StartGameThread();

	Q_SIGNAL void				LaunchThreadGame();
	Q_SIGNAL void				OnGamePlayStop_UIThread(bool);

private:
	QMenuBar			*m_MenuBar;
	QToolBar			*m_MainToolBar;
	QStatusBar			*m_StatusBar;
	QRenderViewport		*m_RenderViewport;
	QPushButton			*m_PlayStopButton;
	QThread				m_GameThread;
	QRenderWindow		*m_RenderWindow;
	QWorkerObject		*m_GameWorker;
	Game				*m_Game;
	QSceneControllerW	*m_SceneController;
	QSlider				*m_SimulationSlider;

	void				_CreateViewportPanel();
	void				_CreateControlPanel();

	void				_CreateRenderViewport(QWidget *parentWidget);
};

//----------------------------------------------------------
