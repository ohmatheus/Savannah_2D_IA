#include "stdafx.h"
#include "QSavannahMainWindow.h"

#include "QRenderWindow.h"
#include "QRenderViewport.h"

#include "QWorkerObject.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QDockWidget>

//----------------------------------------------------------

QSavannahMainWindow::QSavannahMainWindow(QWidget *parent)
:	QMainWindow(parent)
,	m_MenuBar(nullptr)
,	m_MainToolBar(nullptr)
,	m_CentralWidget(nullptr)
,	m_StatusBar(nullptr)
,	m_RenderViewport(nullptr)
{
	Setup();

	StartGameThread();
}

//----------------------------------------------------------

QSavannahMainWindow::~QSavannahMainWindow()
{
	m_GameThread.quit();
	m_GameThread.wait();
}

//----------------------------------------------------------

void	QSavannahMainWindow::Setup()
{
	setObjectName(QString::fromUtf8("SavannahMainWindow"));

	resize(1600, 800);
	m_MenuBar = new QMenuBar(this);
	m_MenuBar->setObjectName(QString::fromUtf8("menuBar"));
	setMenuBar(m_MenuBar);
	m_MainToolBar = new QToolBar(this);
	m_MainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
	addToolBar(m_MainToolBar);
	m_CentralWidget = new QWidget(this);
	m_CentralWidget->setObjectName(QString::fromUtf8("centralWidget"));
	setCentralWidget(m_CentralWidget);
	m_StatusBar = new QStatusBar(this);
	m_StatusBar->setObjectName(QString::fromUtf8("statusBar"));
	setStatusBar(m_StatusBar);

	setWindowTitle("Savannah");

	QMetaObject::connectSlotsByName(this);

	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);

	_CreateControlPanel();
	_CreateViewportPanel();
}

//----------------------------------------------------------

void	QSavannahMainWindow::StartGameThread()
{
	QWorkerObject	*gameWorkerObject = new QWorkerObject();

	gameWorkerObject->SetFunc(std::bind(&QSavannahMainWindow::_GameLoop, this));

	gameWorkerObject->moveToThread(&m_GameThread);

	connect(gameWorkerObject, &QWorkerObject::End, this, []()
	{
		// some usefull stuff here
	});

	connect(&m_GameThread, &QThread::finished, gameWorkerObject, &QObject::deleteLater);

	connect(this, &QSavannahMainWindow::LaunchThreadGame, gameWorkerObject, &QWorkerObject::Play);

	m_GameThread.start();
}

//----------------------------------------------------------

void	QSavannahMainWindow::_CreateViewportPanel()
{
	QDockWidget	*dockw = new QDockWidget(tr("Viewport"));
	dockw->setObjectName("Viewport");

	{
		// m_ViewMenu->addAction(dockw->toggleViewAction());
		// Here add pause/play button

		auto		*dummy = new QWidget(dockw);
		dockw->setWidget(dummy);

		auto		*layout = new QVBoxLayout(dummy);
		layout->setSpacing(0);
		layout->setContentsMargins(0, 0, 0, 0);

		const std::string	viewportName = "Savannah Game";

		_CreateRenderViewport(this);

		assert(m_RenderViewport != nullptr);

		layout->addWidget(m_RenderViewport);
	}

	dockw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);	// Horizontally greedy: expands if possible

	addDockWidget(Qt::TopDockWidgetArea, dockw);

	// We should create a render system, that's hold all the rendering controll, including threading
}

//----------------------------------------------------------

void	QSavannahMainWindow::_CreateControlPanel()
{

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

void	QSavannahMainWindow::_GameLoop()
{
	m_RenderWindow->Initialize();
	while (true)
	{
		bool		continueRunning = false;
		const auto	topWidgets = QApplication::topLevelWidgets();
		for (int i = 0; i < topWidgets.size(); ++i)
		{
			if (topWidgets[i]->isVisible())
			{
				continueRunning = true;
				break;
			}
		}
		if (!continueRunning)
			break;



		m_RenderWindow->SwapBuffers();
		QThread::sleep(0.01);
	}
}

//----------------------------------------------------------

