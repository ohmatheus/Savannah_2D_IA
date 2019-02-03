#include "stdafx.h"

#include "Game.h"
#include "IGameWindow.h"

#include "RenderSystem.h"
#include "GridScene.h"
#include "Timer.h"

//
#include "GLShader.h"
//

#include <QApplication> // temp
#include <QWidget> // temp
#include <QThread> // temp
#include <QTimer> // temp
#include <QEvent> // temp
#include <QKeyEvent> // temp

#include <iostream>

//----------------------------------------------------------

Game::Game(IGameController *controller, IGameWindow *renderWindow)
:	m_RenderWindow(renderWindow)
,	m_GameController(controller)
{
	assert(m_RenderWindow != nullptr);

	m_RenderWindowData = new SRenderWindowData;

	m_ViewProj = glm::mat4(1.f);

	m_Events = new std::vector<QEvent*>;
	m_Events->reserve(1000);
}

//----------------------------------------------------------

Game::~Game()
{
	for (int i = 0; i < m_Events->size(); ++i)
		delete (*m_Events)[i];
	m_Events->clear();
	delete m_Events;

	for (int i = 0; i < m_Scenes.size(); ++i)
		delete m_Scenes[i];
	m_Scenes.clear();
	if (m_IsGameRunning)
		delete m_CurrentScene;
	delete m_RenderSystem;
	delete m_RenderWindowData;
}

//----------------------------------------------------------

void	Game::StartAndLoop()
{
	m_RenderWindow->Initialize();
	_InitRenderSystem();

	GridScene *scene = new GridScene(this);
	m_Scenes.push_back(scene);

	m_CurrentScene = scene;

	m_GameParameters = m_CurrentScene->Parameters();
	Q_EMIT OnSceneParamsChanged(m_GameParameters);

	Timer timer;
	float		dt = 0.f;
	const float fixedSimulationFramerate = 60.f; // max dt
	float		limitedDt = 0;
	timer.Start();

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


		dt = timer.Stop();
		timer.Start();
		// fix framerate (not very precise tho... but good enough)
		{
			const float		dtLimit = 1.0f / fixedSimulationFramerate;
			const float		timeDelta = dtLimit - dt;
			const float		timeToWait = (timeDelta * 1.0e+3f) - 1.0f;

			if (dt > dtLimit)
				dt = dtLimit;

			if (timeToWait > 0.f)
				QThread::msleep(uint(timeToWait));
		}

		_GetParametersFromController();
		_CheckTogglePlayStop();
		m_RenderWindow->SwapEvents(m_Events);
		ProcessEvents(dt);
		assert(m_Events->empty());
		_PostEvent();

		m_RenderWindow->SwapRenderData(m_RenderWindowData);
		m_RenderWindow->MakeCurrent();

		_ProcessRenderData();
		//if (!m_RenderWindowData->m_ContinueRunning); 
		//	break;

		if (!m_Paused && m_IsGameRunning)
		{
			m_CurrentScene->PreUpdate(dt * m_SimulationSpeed);
			m_CurrentScene->Update(dt * m_SimulationSpeed);
		}

		m_RenderSystem->PreRender();
		m_CurrentScene->Render(m_RenderSystem);

		m_RenderWindow->SwapBuffers();
	}
}

//----------------------------------------------------------

void	Game::ProcessEvents(float dt)
{
	for (int i = 0; i < m_Events->size(); i++)
	{
		QEvent *ev = (*m_Events)[i];
		_ProcessEvent(ev, dt);
		delete ev;
	}

	m_Events->clear();
}

//----------------------------------------------------------

void	Game::TooglePlayStop()
{
	SCOPEDLOCK(m_UILock);
	m_TogglePlayStop = true;
}

//----------------------------------------------------------

void	Game::_LaunchScene()
{
	m_CurrentScene = m_Scenes[0]->Clone();
	m_CurrentScene->OnSceneStart();
	m_IsGameRunning = true;
	m_Paused = false;
	Q_EMIT(OnGamePlayStop(m_IsGameRunning));
}

//----------------------------------------------------------

void	Game::_StopScene()
{
	if (m_CurrentScene != nullptr)
	{
		delete m_CurrentScene;
	}
	m_CurrentScene = m_Scenes[0];
	m_IsGameRunning = false;
	m_Paused = false;
	Q_EMIT(OnGamePlayStop(m_IsGameRunning));
}

//----------------------------------------------------------

void	Game::_CheckTogglePlayStop()
{
	SCOPEDLOCK(m_UILock);
	if (m_TogglePlayStop)
	{
		if (!m_IsGameRunning)
			_LaunchScene();
		else
			_StopScene();
		m_TogglePlayStop = false;
	}
}

//----------------------------------------------------------

void	Game::_GetParametersFromController()
{
	if (m_GameController->RequestGameParameters(m_GameParameters))
	{
		m_CurrentScene->SetParameters(m_GameParameters);
		m_SimulationSpeed = m_GameParameters.m_SimulationSpeed;
	}
}

//----------------------------------------------------------

void	Game::_ProcessRenderData()
{
	assert(m_RenderWindowData != nullptr);
	if (m_RenderWindowData->m_Dirty)
	{
		glViewport(0, 0, m_RenderWindowData->m_X, m_RenderWindowData->m_Y);

		m_OrthoMat = glm::ortho(-1.f, 1.0f, -1.f, 1.0f, 0.1f, 200.0f);
		m_ProjMat = glm::perspective(glm::radians(m_Fov), m_RenderWindowData->m_X / m_RenderWindowData->m_Y, 0.1f, 200.0f);

		// VClip = proj * view * model * local
		m_ViewProj = m_Camera.GetView() * m_ProjMat;

		m_RenderWindowData->m_Dirty = false;
	}
}

//----------------------------------------------------------

void	Game::_PostEvent()
{
	//if (m_Camera.m_Position.z < -8.f)
	//	m_Camera.m_Position.z = -8.f;
	if (m_Camera.m_Position.z > -1.f)
		m_Camera.m_Position.z = -1.f;
}

//----------------------------------------------------------

void	Game::_InitRenderSystem()
{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glewInit failed";
		return;
	}
	m_RenderSystem = new RenderSystem(this);

	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 800, 600); // resize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_RenderWindow->SwapBuffers();

	{
		m_OrthoMat = glm::ortho(-400.f, 400.0f, -300.f, 300.0f, 0.1f, 200.0f);
		m_ProjMat = glm::perspective(glm::radians(m_Fov), 800.f / 600.f, 0.1f, 200.0f);

		m_ViewProj = m_ProjMat * m_Camera.GetView();
	}
}

//----------------------------------------------------------

void	Game::_ProcessEvent(QEvent *ev, float dt)
{
	switch (ev->type())
	{
	case QEvent::MouseMove:
		MouseMoveEvent((QMouseEvent*)ev, dt);
		break;
	case QEvent::MouseButtonPress:
		MousePressEvent((QMouseEvent*)ev, dt);
		break;
	case QEvent::MouseButtonRelease:
		MouseReleaseEvent((QMouseEvent*)ev, dt);
		break;
	case QEvent::Wheel:
		WheelEvent((QWheelEvent*)ev, dt);
		break;
	case QEvent::KeyPress:
	{
		QKeyEvent *k = (QKeyEvent *)ev;
		KeyPressEvent(k, dt);
		break;
	}
	case QEvent::KeyRelease:
		KeyReleaseEvent((QKeyEvent*)ev, dt);
		break;

	default: break;
	}
}

//----------------------------------------------------------

void	Game::KeyPressEvent(QKeyEvent *ev, float dt)
{
	if (m_IsGameRunning)
	{
		if (ev->key() == Qt::Key_Space)
			m_Paused = !m_Paused;
	}

	if (ev->key() == Qt::Key_P)
	{
		TooglePlayStop();
	}
}

//----------------------------------------------------------

void	Game::KeyReleaseEvent(QKeyEvent *ev, float dt)
{

}

//----------------------------------------------------------

void	Game::MousePressEvent(QMouseEvent *ev, float dt)
{

}

//----------------------------------------------------------

void	Game::MouseReleaseEvent(QMouseEvent *ev, float dt)
{

}

//----------------------------------------------------------

void	Game::MouseDoubleClickEvent(QMouseEvent *ev, float dt)
{

}

//----------------------------------------------------------

void	Game::MouseMoveEvent(QMouseEvent *ev, float dt)
{

}

//----------------------------------------------------------

void	Game::WheelEvent(QWheelEvent *ev, float dt)
{
	QPoint	pt = ev->angleDelta();
	const int	degrees = pt.y() / 8;
	const int	steps = degrees / 15;
	m_Camera.m_Position += glm::vec3(0.f, 0.f, 5.f) * dt * float(steps);
}

//----------------------------------------------------------
