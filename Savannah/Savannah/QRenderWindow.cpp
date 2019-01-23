#include "stdafx.h"

#include "QRenderWindow.h"
#include "QRenderViewport.h"

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
}

void	QRenderWindow::Initialize_GameThread()
{
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
		//m_Context->getProcAddress("glGenBuffers");

		//m_Context->functions()
		//glGenBuffers(GL_ARRAY_BUFFER, &VBO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);


	}
}

//----------------------------------------------------------

void	QRenderWindow::SwapBuffers()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_Context->swapBuffers(this);
}

//----------------------------------------------------------
