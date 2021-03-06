#include "stdafx.h"
#include "QSavannahMainWindow.h"

#include "QRenderWindow.h"
#include "QRenderViewport.h"

#include "QWorkerObject.h"

#include "Game.h"

#include "QSceneControllerW.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>

//----------------------------------------------------------

QSavannahMainWindow::QSavannahMainWindow(QWidget *parent)
:	QMainWindow(parent)
,	m_MenuBar(nullptr)
,	m_MainToolBar(nullptr)
,	m_StatusBar(nullptr)
,	m_RenderViewport(nullptr)
,	m_Game(nullptr)
{
	Setup();
	StartGameThread();
}

//----------------------------------------------------------

QSavannahMainWindow::~QSavannahMainWindow()
{
	m_GameThread.quit();
	m_GameThread.wait();

	if (m_Game != nullptr)
		delete m_Game;
	delete m_RenderWindow;
}

//----------------------------------------------------------

void	QSavannahMainWindow::Setup()
{
	setObjectName(QString::fromUtf8("SavannahMainWindow"));

	m_MenuBar = new QMenuBar(this);
	m_MenuBar->setObjectName(QString::fromUtf8("menuBar"));
	setMenuBar(m_MenuBar);
	
	m_StatusBar = new QStatusBar(this);
	m_StatusBar->setObjectName(QString::fromUtf8("statusBar"));
	setStatusBar(m_StatusBar);

	setWindowTitle("Savannah");

	QMetaObject::connectSlotsByName(this);

	_CreateControlPanel();
	_CreateViewportPanel();

	assert(m_SceneController != nullptr);
	m_Game = new Game(m_SceneController, m_RenderWindow);
	m_RenderWindow->SetGame(m_Game);

	m_RenderViewport->setFocus();

	// all connections
	connect(this, &QSavannahMainWindow::OnGamePlayStop_UIThread, this, [this](bool isrunning)
	{
		this->m_SceneController->setEnabled(!isrunning);
	});

	connect(m_Game, &Game::OnGamePlayStop, this, [this](bool isrunning)
	{
		if (isrunning)
			this->m_PlayStopButton->setText("Stop");
		else
			this->m_PlayStopButton->setText("Play");
		Q_EMIT this->OnGamePlayStop_UIThread(isrunning);
	});
	
	connect(m_PlayStopButton, &QPushButton::clicked, [this]()
	{
		this->m_Game->TooglePlayStop();
	});

	connect(m_SimulationSlider, &QSlider::valueChanged, [this](int value)
	{
		this->m_SceneController->SetSimulationSpeed(value * 0.01f);
	});

	connect(m_Game, &Game::OnSceneParamsChanged, [this](const SGameParameters &params)
	{
		this->m_SceneController->SetGameParameters(params);
	});
}

//----------------------------------------------------------

void	QSavannahMainWindow::StartGameThread()
{
	m_GameWorker = new QWorkerObject();

	m_GameWorker->SetFunc([this]()
	{
		m_Game->StartAndLoop();
	});// std::bind(&Game::StartAndLoop, m_Game));

	m_GameWorker->moveToThread(&m_GameThread);

	connect(m_GameWorker, &QWorkerObject::End, this, []()
	{
		// some usefull stuff here
		// TODO close app properly
	});

	connect(&m_GameThread, &QThread::finished, m_GameWorker, &QObject::deleteLater);

	connect(this, &QSavannahMainWindow::LaunchThreadGame, m_GameWorker, &QWorkerObject::Play);
	
	m_GameThread.start();
}

//----------------------------------------------------------

void	QSavannahMainWindow::_CreateViewportPanel()
{
	QDockWidget	*dockw = new QDockWidget(tr("Viewport"), this);
	dockw->setObjectName("Viewport");

	{
		auto		*dummy = new QWidget(dockw);
		dockw->setWidget(dummy);

		auto		*layout = new QVBoxLayout(dummy);
		layout->setSpacing(0);
		layout->setContentsMargins(0, 0, 0, 0);

		const std::string	viewportName = "Savannah Game";

		m_MainToolBar = new QToolBar(dockw);
		m_MainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
		addToolBar(m_MainToolBar);
		layout->addWidget(m_MainToolBar);

		m_PlayStopButton = new QPushButton("Play", this);
		m_MainToolBar->addWidget(m_PlayStopButton);

		m_SimulationSlider = new QSlider(Qt::Orientation::Horizontal, this);
		m_SimulationSlider->setMaximum(200);
		m_SimulationSlider->setMinimum(0);
		m_SimulationSlider->setValue(100);
		m_SimulationSlider->setMaximumWidth(200);
		m_MainToolBar->addWidget(m_SimulationSlider);

		_CreateRenderViewport(this);

		assert(m_RenderViewport != nullptr);

		layout->addWidget(m_RenderViewport);
	}

	dockw->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);	// Horizontally greedy: expands if possible
	dockw->setAllowedAreas(Qt::AllDockWidgetAreas);
	addDockWidget(Qt::LeftDockWidgetArea, dockw);
}

//----------------------------------------------------------

void	QSavannahMainWindow::_CreateControlPanel()
{
	QDockWidget	*dockw = new QDockWidget(tr("Control"), this);
	dockw->setObjectName("Control");

	{
		auto		*dummy = new QWidget(dockw);
		dockw->setWidget(dummy);

		auto		*layout = new QVBoxLayout(dummy);
		layout->setSpacing(0);

		dummy->setMaximumSize(QSize(400, 2000));

		m_SceneController = new QSceneControllerW(this);
		layout->addWidget(m_SceneController);
	}
	dockw->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);	// Horizontally greedy: expands if possible
	dockw->setAllowedAreas(Qt::RightDockWidgetArea);

	addDockWidget(Qt::RightDockWidgetArea, dockw);
}

//----------------------------------------------------------

void	QSavannahMainWindow::_CreateRenderViewport(QWidget *parentWidget)
{
	QRenderViewport		*viewport = new QRenderViewport(parentWidget);
	m_RenderWindow = new QRenderWindow();

	assert(viewport != nullptr);
	assert(m_RenderWindow != nullptr);

	QWidget				*container = QWidget::createWindowContainer(m_RenderWindow, viewport); // The container takes over ownership of window.
	assert(container != nullptr);

	container->setMinimumSize(200, 200); // (1, 1)
	container->setAutoFillBackground(false);
	container->setAcceptDrops(false);

	m_RenderWindow->setSurfaceType(QWindow::OpenGLSurface);
	m_RenderWindow->create();
	viewport->Setup(container, m_RenderWindow);

	m_RenderViewport = viewport;
}

//----------------------------------------------------------

