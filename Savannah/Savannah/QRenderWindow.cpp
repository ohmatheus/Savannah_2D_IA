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

	
	//m_Context->makeCurrent(this);

	//if (glewInit() != GLEW_OK)
	//{
	//	//CLog::Log(PK_ERROR, "glewInit failed");
	//	return;
	//}

	assert(QCoreApplication::testAttribute(Qt::AA_ShareOpenGLContexts) == true);

	m_SurfaceFormat = new QSurfaceFormat();

//	if (!POPED_VERIFY(m_SurfaceFormat != null))
//		return false;

	QSurfaceFormat		&format = *m_SurfaceFormat;
	format.setOptions(QSurfaceFormat::DebugContext);
	format.setDepthBufferSize(16);
	format.setVersion(4, 1);
	format.setProfile(QSurfaceFormat::CoreProfile);

	m_Context = new QOpenGLContext();

	m_Context->setFormat(format);
	

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

	glClearColor(1.0f, 0.0f, 0.4f, 0.0f);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//----------------------------------------------------------
