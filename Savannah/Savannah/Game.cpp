﻿#include "stdafx.h"

#include "Game.h"
#include "IGameWindow.h"

#include "RenderSystem.h"
#include "Scene.h"
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

Game::Game(IGameWindow *renderWindow)
:	m_RenderWindow(renderWindow)
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
	for (int i = 0; i < m_Scenes.size(); ++i)
		delete m_Scenes[i];
	m_Scenes.clear();
	delete m_RenderSystem;
	delete m_RenderWindowData;
}

//----------------------------------------------------------

void	Game::StartAndLoop()
{
	m_RenderWindow->Initialize();
	_InitRenderSystem();

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

		//assert(m_Events->empty());
		m_RenderWindow->SwapEvents(m_Events);
		ProcessEvents();
		assert(m_Events->empty());

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

		m_RenderWindow->SwapRenderData(m_RenderWindowData);
		m_RenderWindow->MakeCurrent();

		_ProcessRenderData();
		//if (!m_RenderWindowData->m_ContinueRunning); 
		//	break;

		if (!m_Paused)
			m_Scenes[0]->Update(dt * m_SimulationSpeed);

		m_RenderSystem->PreRender();
		m_Scenes[0]->Render(m_RenderSystem);

		m_RenderWindow->SwapBuffers();
	}
}

//----------------------------------------------------------

void	Game::ProcessEvents()
{
	for (int i = 0; i < m_Events->size(); i++)
	{
		QEvent *ev = (*m_Events)[i];
		_ProcessEvent(ev);
	}

	m_Events->clear();
}

//----------------------------------------------------------

void	Game::_ProcessRenderData()
{
	assert(m_RenderWindowData != nullptr);
	if (m_RenderWindowData->m_Dirty)
	{
		glViewport(0, 0, m_RenderWindowData->m_X, m_RenderWindowData->m_Y);

		m_OrthoMat = glm::ortho(-1.f, 1.0f, -1.f, 1.0f, 0.1f, 100.0f);
		m_ProjMat = glm::perspective(glm::radians(m_Fov), m_RenderWindowData->m_X / m_RenderWindowData->m_Y, 0.1f, 100.0f);

		// VClip = proj * view * model * local
		m_ViewProj = m_Camera.GetView() * m_ProjMat;

		m_RenderWindowData->m_Dirty = false;
	}
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


	Scene *scene = new Scene();
	m_Scenes.push_back(scene);

	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	glClearDepth(1.f);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 800, 600); // resize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_RenderWindow->SwapBuffers();

	{
		m_OrthoMat = glm::ortho(-400.f, 400.0f, -300.f, 300.0f, 0.1f, 100.0f);
		m_ProjMat = glm::perspective(glm::radians(m_Fov), 800.f / 600.f, 0.1f, 100.0f);

		m_ViewProj = m_ProjMat * m_Camera.GetView();
	}
}

//----------------------------------------------------------

void	Game::_ProcessEvent(QEvent *ev)
{
	switch (ev->type())
	{
	case QEvent::MouseMove:
		mouseMoveEvent((QMouseEvent*)ev);
		break;
	case QEvent::MouseButtonPress:
		mousePressEvent((QMouseEvent*)ev);
		break;
	case QEvent::MouseButtonRelease:
		mouseReleaseEvent((QMouseEvent*)ev);
		break;
	case QEvent::Wheel:
		wheelEvent((QWheelEvent*)ev);
		break;
	case QEvent::KeyPress:
	{
		QKeyEvent *k = (QKeyEvent *)ev;
		keyPressEvent(k);
		break;
	}
	case QEvent::KeyRelease:
		keyReleaseEvent((QKeyEvent*)ev); 
		break;

	default: break;
	}
}

//----------------------------------------------------------

void	Game::keyPressEvent(QKeyEvent *ev)
{
	if (ev->key() == Qt::Key_Space)
		m_Paused = !m_Paused;
}

//----------------------------------------------------------

void	Game::keyReleaseEvent(QKeyEvent *ev)
{

}

//----------------------------------------------------------

void	Game::mousePressEvent(QMouseEvent *ev)
{

}

//----------------------------------------------------------

void	Game::mouseReleaseEvent(QMouseEvent *ev)
{

}

//----------------------------------------------------------

void	Game::mouseDoubleClickEvent(QMouseEvent *ev)
{

}

//----------------------------------------------------------

void	Game::mouseMoveEvent(QMouseEvent *ev)
{

}

//----------------------------------------------------------

void	Game::wheelEvent(QWheelEvent *)
{

}

//----------------------------------------------------------
