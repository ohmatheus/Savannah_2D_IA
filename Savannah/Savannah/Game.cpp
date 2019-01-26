#include "stdafx.h"

#include "Game.h"
#include "IGameWindow.h"

#include "RenderSystem.h"
#include "Scene.h"

//
#include "GLShader.h"
//

#include <QApplication> // temp
#include <QWidget> // temp
#include <QThread> // temp

#include <iostream>

//----------------------------------------------------------

Game::Game(IGameWindow *renderWindow)
:	m_RenderWindow(renderWindow)
{
	assert(m_RenderWindow != nullptr);

	m_RenderWindowData = new SRenderWindowData;

	m_ViewProj = glm::mat4(1.f);
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

	float dt = 0.f;

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

		m_RenderWindow->SwapRenderData(m_RenderWindowData);
		m_RenderWindow->MakeCurrent();

		_ProcessRenderData();

		// Update
		m_Scenes[0]->Update(dt);
		//if (!m_RenderWindowData->m_ContinueRunning); 
		//	break;


		// renderring
		m_RenderSystem->PreRender();

		m_Scenes[0]->Render(m_RenderSystem);

		m_RenderWindow->SwapBuffers();
		QThread::sleep(0.01);
	}
}

//----------------------------------------------------------

void	Game::_ProcessRenderData()
{
	assert(m_RenderWindowData != nullptr);
	if (m_RenderWindowData->m_Dirty)
	{
		glViewport(0, 0, m_RenderWindowData->m_X, m_RenderWindowData->m_Y);

		m_OrthoMat = glm::ortho(-1.f, 1.0f, -1.f, 1.0f, 0.1f, 100.0f); // fucked
		m_ProjMat = glm::perspective(glm::radians(45.0f), m_RenderWindowData->m_X / m_RenderWindowData->m_Y, 0.1f, 100.0f);

		// VClip = proj * view * model * local
		m_ViewProj = m_ProjMat * m_Camera.GetView();

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
	glViewport(0, 0, 800, 600); // resize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_RenderWindow->SwapBuffers();

	// init object
	{
		//transformModel = glm::rotate(transformModel, glm::radians(90.f), glm::vec3(0.0, 0.0, 1.0));

		m_OrthoMat = glm::ortho(-400.f, 400.0f, -300.f, 300.0f, 0.1f, 100.0f);
		m_ProjMat = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);

		m_ViewProj = m_ProjMat * m_Camera.GetView();
	}
}

//----------------------------------------------------------
