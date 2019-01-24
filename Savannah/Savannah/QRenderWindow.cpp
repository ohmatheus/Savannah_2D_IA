#include "stdafx.h"

#include "QRenderWindow.h"
#include "QRenderViewport.h"

#include "GLShader.h"

#include <iostream>

#include <QCoreApplication>
#include <QOpenGLContext>

//#define glGenBuffers GLEW_GET_FUN(__glewGenBuffers)

//----------------------------------------------------------

QRenderWindow::QRenderWindow()
:	Super()
,	m_Viewport(nullptr)
{

}

//----------------------------------------------------------

QRenderWindow::~QRenderWindow()
{
	delete m_SurfaceFormat;
}

//----------------------------------------------------------

void	QRenderWindow::SetRenderViewport(QRenderViewport *viewport)
{
	m_Viewport = viewport;

	assert(QCoreApplication::testAttribute(Qt::AA_ShareOpenGLContexts) == true);
}

//----------------------------------------------------------

// temp
namespace
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	unsigned int VAO;

	char *vertexShader =
		"#version 410 core											\n"
		"	layout(location = 0) in vec3 aPos;						\n"
		"void main()												\n"
		"{															\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);		\n"
		"}															\n"
		;

	char *fragShader =
		"#version 410 core											\n"
		"out vec4 FragColor;										\n"
		"void main()												\n"
		"{															\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);				\n"
		"}															\n"
		;

	GLShader shader;
}

void	QRenderWindow::Initialize_GameThread()
{
	SCOPEDLOCK(m_WindowLock);
	m_SurfaceFormat = new QSurfaceFormat();

	m_SurfaceFormat->setOptions(QSurfaceFormat::DebugContext);
	m_SurfaceFormat->setDepthBufferSize(16);
	m_SurfaceFormat->setVersion(4, 1);
	m_SurfaceFormat->setProfile(QSurfaceFormat::CoreProfile);

	//QOpenGLContext* sharectx = QOpenGLContext::currentContext();

	m_Context = new QOpenGLContext();

	//sharectx->setShareContext(m_Context);

	m_Context->setFormat(*m_SurfaceFormat);

	if (!m_Context->create())
	{
		std::cout << "Could not create OpenGL context !";
		return;
	}

	if (!m_Context->makeCurrent(this))
	{
		std::cout << "Could not activate OpenGL context !";
		return;
	}

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glewInit failed";
		return;
	}

	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	glViewport(0, 0, 800, 600); // resize
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_Context->swapBuffers(this);

	// init object
	{
		shader.LoadShader(GLShader::VERTEX_SHADER, vertexShader);
		shader.LoadShader(GLShader::FRAGMENT_SHADER, fragShader);
		shader.CreateAndLink();
		shader.Bind();
		{
			// attribute and uniforms
		}
		shader.Unbind();
		shader.m_name = "Test";

		glGenVertexArrays(1, &VAO);

		// create buffer
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

void	QRenderWindow::SwapBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.Bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	m_Context->swapBuffers(this);
}

//----------------------------------------------------------
