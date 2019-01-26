#include "stdafx.h"

#include "Game.h"
#include "IGameWindow.h"

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
}

//----------------------------------------------------------

Game::~Game()
{}

//----------------------------------------------------------

// temp
namespace
{
	float vertices[] = {
		-0.5f,	-0.5f,	-2.5f,
		0.5f,	-0.5f,	-2.5f,
		0.0f,	0.5f,	-2.5f
	};

	unsigned int VBO;
	unsigned int VAO;

	glm::mat4	transformModel = glm::mat4(1.0f);
	glm::mat4	view = glm::mat4(1.0f);
	glm::mat4	viewProj;

	glm::mat4	orthoMat;
	glm::mat4	projMat;

	char *vertexShader =
		"#version 410 core												\n"
		"layout(location = 0) in vec3 aPos;								\n"
		"uniform mat4 viewProj;											\n"
		"uniform mat4 modelTransform;									\n"
		"void main()													\n"
		"{																\n"
		"	gl_Position = viewProj * modelTransform * vec4(aPos, 1.0f);	\n"
		"}																\n"
		;

	char *fragShader =
		"#version 410 core											\n"
		"out vec4		FragColor;									\n"
		"uniform vec4	uColor;										\n"
		"void main()												\n"
		"{															\n"
		"	FragColor = uColor;										\n"
		"}															\n"
		;

	GLShader shader;
}

//----------------------------------------------------------

void	Game::StartAndLoop()
{
	m_RenderWindow->Initialize();
	_InitRenderSystem();

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
		//if (!m_RenderWindowData->m_ContinueRunning); 
		//	break;


		// renderring
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Bind();
		glUniformMatrix4fv(shader("modelTransform"), 1, GL_FALSE, glm::value_ptr(transformModel));
		glUniformMatrix4fv(shader("viewProj"), 1, GL_FALSE, glm::value_ptr(viewProj));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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

		orthoMat = glm::ortho(-1.f, 1.0f, -1.f, 1.0f, 0.1f, 100.0f); // fucked
		projMat = glm::perspective(glm::radians(45.0f), m_RenderWindowData->m_X / m_RenderWindowData->m_Y, 0.1f, 100.0f);

		// VClip = proj * view * model * local
		viewProj = projMat * view;

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

	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	glViewport(0, 0, 800, 600); // resize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_RenderWindow->SwapBuffers();

	// init object
	{
		//transformModel = glm::rotate(transformModel, glm::radians(90.f), glm::vec3(0.0, 0.0, 1.0));

		orthoMat = glm::ortho(-400.f, 400.0f, -300.f, 300.0f, 0.1f, 100.0f);
		projMat = glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 100.0f);

		//Vclip = Mprojection⋅Mview⋅Mmodel⋅Vlocal
		viewProj = projMat * view;

		shader.LoadShader(GLShader::VERTEX_SHADER, vertexShader);
		shader.LoadShader(GLShader::FRAGMENT_SHADER, fragShader);
		shader.CreateAndLink();
		shader.Bind();
		{
			shader.AddUniform("uColor");
			glUniform4f(shader("uColor"), 0.0f, 1.f, 0.0f, 1.0f);
			shader.AddUniform("modelTransform");
			shader.AddUniform("viewProj");
		}
		shader.Unbind();

		shader.m_name = "Test";

		// vertex buffer object and create buffers
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		// bind, 1 possible in the same time / buffer type
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// copies data in the buffers memory
		// GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
		// GL_DYNAMIC_DRAW : the data is likely to change a lot.
		// GL_STREAM_DRAW : the data will change every time it is drawn.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}
}

//----------------------------------------------------------
