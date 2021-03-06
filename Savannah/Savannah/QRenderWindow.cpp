﻿#include "stdafx.h"

#include "QRenderWindow.h"
#include "QRenderViewport.h"

#include "GLShader.h"

#include "Game.h"

#include <iostream>

#include <QCoreApplication>
#include <QOpenGLContext>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QWheelEvent>

//----------------------------------------------------------

QRenderWindow::QRenderWindow()
:	Super()
,	m_Viewport(nullptr)
,	m_RenderWindowData_UIThread(nullptr)
{
	m_RenderWindowData_UIThread = new SRenderWindowData;
	m_EventsToSend = new std::vector<QEvent*>;
	m_EventsToSend->reserve(1000);
}

//----------------------------------------------------------

QRenderWindow::~QRenderWindow()
{
	{
		SCOPEDLOCK(m_EventLock);
		for (int i = 0; i < m_EventsToSend->size(); ++i)
			delete (*m_EventsToSend)[i];
		m_EventsToSend->clear();
		delete m_EventsToSend;
	}

	if (m_SurfaceFormat != nullptr)
		delete m_SurfaceFormat;
	if (m_Context != nullptr)
		delete m_Context;
	if (m_RenderWindowData_UIThread != nullptr)
		delete m_RenderWindowData_UIThread;

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

	m_SurfaceFormat->setOptions(QSurfaceFormat::DebugContext);
	m_SurfaceFormat->setDepthBufferSize(16);
	m_SurfaceFormat->setVersion(4, 1);
	m_SurfaceFormat->setProfile(QSurfaceFormat::CoreProfile);
	m_SurfaceFormat->setSwapBehavior(QSurfaceFormat::DoubleBuffer);

	setFormat(*m_SurfaceFormat);

	//QOpenGLContext *context = QOpenGLContext::currentContext();
	//assert(context != nullptr);

	m_Context = new QOpenGLContext(this);

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

void	QRenderWindow::SwapEvents(std::vector<QEvent*> *&outEvents)
{
	SCOPEDLOCK(m_EventLock);
	if (!m_EventsToSend->empty())
	{
		//assert(outEvents->empty());
		std::vector<QEvent*> *temp = outEvents;
		outEvents = m_EventsToSend;
		m_EventsToSend = temp;
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
	m_Context->makeCurrent(this);
	m_Context->swapBuffers(this);
	m_Context->makeCurrent(this);
}

//----------------------------------------------------------

void	QRenderWindow::keyPressEvent(QKeyEvent *ev)
{
	Super::keyPressEvent(ev);
	{
		SCOPEDLOCK(m_EventLock);
		m_EventsToSend->push_back(new QKeyEvent(*ev));
	}
}

//----------------------------------------------------------

void	QRenderWindow::keyReleaseEvent(QKeyEvent *ev)
{
	Super::keyReleaseEvent(ev);
	{
		SCOPEDLOCK(m_EventLock);
		m_EventsToSend->push_back(new QKeyEvent(*ev));
	}
}

//----------------------------------------------------------

void	QRenderWindow::mousePressEvent(QMouseEvent *ev)
{
	Super::mousePressEvent(ev);
	{
		SCOPEDLOCK(m_EventLock);
		m_EventsToSend->push_back(new QMouseEvent(*ev));
	}
}

//----------------------------------------------------------

void	QRenderWindow::mouseReleaseEvent(QMouseEvent *ev)
{
	Super::mouseReleaseEvent(ev);
	{
		SCOPEDLOCK(m_EventLock);
		m_EventsToSend->push_back(new QMouseEvent(*ev));
	}
}

//----------------------------------------------------------

void	QRenderWindow::mouseDoubleClickEvent(QMouseEvent *ev)
{
	Super::mouseDoubleClickEvent(ev);
	{
		SCOPEDLOCK(m_EventLock);
		m_EventsToSend->push_back(new QMouseEvent(*ev));
	}
}

//----------------------------------------------------------

void	QRenderWindow::mouseMoveEvent(QMouseEvent *ev)
{
	Super::mouseMoveEvent(ev);
	{
		SCOPEDLOCK(m_EventLock);
		m_EventsToSend->push_back(new QMouseEvent(*ev));
	}
}

//----------------------------------------------------------

void	QRenderWindow::wheelEvent(QWheelEvent *ev)
{
	Super::wheelEvent(ev);
	{
		SCOPEDLOCK(m_EventLock);
		m_EventsToSend->push_back(new QWheelEvent(*ev));
	}
}

//----------------------------------------------------------
