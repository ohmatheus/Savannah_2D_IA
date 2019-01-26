#include "stdafx.h"

#include "QRenderWindow.h"
#include "QRenderViewport.h"

#include "GLShader.h"

#include <iostream>

#include <QCoreApplication>
#include <QOpenGLContext>

//----------------------------------------------------------

QRenderWindow::QRenderWindow()
:	Super()
,	m_Viewport(nullptr)
,	m_RenderWindowData_UIThread(nullptr)
{
	m_RenderWindowData_UIThread = new SRenderWindowData;
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

void	QRenderWindow::Initialize()
{
	SCOPEDLOCK(m_WindowLock);
	m_SurfaceFormat = new QSurfaceFormat();

	//m_RenderWindowData_GameThread = new SRenderWindowData;

	m_SurfaceFormat->setOptions(QSurfaceFormat::DebugContext);
	m_SurfaceFormat->setDepthBufferSize(16);
	m_SurfaceFormat->setVersion(4, 1);
	m_SurfaceFormat->setProfile(QSurfaceFormat::CoreProfile);

	m_Context = new QOpenGLContext();

	m_Context->setFormat(*m_SurfaceFormat);

	if (!m_Context->create())
	{
		std::cout << "Could not create OpenGL context !";
		return;
	}

	if (!m_Context->makeCurrent(this))
	{
		std::cout << "Could not activate OpenGL context !";
		assert(false);
		return;
	}
}

//----------------------------------------------------------

void	QRenderWindow::SwapRenderData(SRenderWindowData *&outRenderData)
{
	SCOPEDLOCK(m_WindowLock);
	if (m_RenderWindowData_UIThread->m_Dirty)
	{
		SRenderWindowData *temp = outRenderData;
		outRenderData = m_RenderWindowData_UIThread;
		m_RenderWindowData_UIThread = temp;
		m_RenderWindowData_UIThread->Clear();
	}
}

//----------------------------------------------------------

void	QRenderWindow::MakeCurrent()
{
	if (!m_Context->makeCurrent(this))
	{
		std::cout << "Could not make current OpenGL context !";
		return;
	}
}

//----------------------------------------------------------

void	QRenderWindow::SetViewportSize(float x, float y)
{
	m_RenderWindowData_UIThread->m_Dirty = true;
	m_RenderWindowData_UIThread->m_X = x;
	m_RenderWindowData_UIThread->m_Y = y;
}

//----------------------------------------------------------

void	QRenderWindow::SwapBuffers()
{
	m_Context->swapBuffers(this);
}

//----------------------------------------------------------
