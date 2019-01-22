#include "stdafx.h"

#include "QRenderWindow.h"
#include "QRenderViewport.h"

#include <QOpenGLContext>

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

	m_SurfaceFormat = new QSurfaceFormat();

	m_SurfaceFormat->setOptions(QSurfaceFormat::DebugContext);
	m_SurfaceFormat->setDepthBufferSize(16);
	m_SurfaceFormat->setVersion(4, 1);
	m_SurfaceFormat->setProfile(QSurfaceFormat::CoreProfile);

	m_Context = new QOpenGLContext();

	m_Context->setFormat(*m_SurfaceFormat);

	if (!m_Context->create())
	{
		//CLog::Log(PK_ERROR, "Could not create OpenGL context !");
		return;
	}

	if (!m_Context->makeCurrent(this))
	{
		//CLog::Log(PK_ERROR, "Could not activate OpenGL context !");
		return;
	}

	if (glewInit() != GLEW_OK)
	{
		//CLog::Log(PK_ERROR, "glewInit failed");
		return;
	}

	glClearColor(1.0f, 0.0f, 0.4f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_Context->swapBuffers(this);
}

//----------------------------------------------------------

void	QRenderWindow::SwapBuffers()
{
	m_Context->swapBuffers(this);
}

//----------------------------------------------------------
