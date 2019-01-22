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

}

//----------------------------------------------------------

void	QRenderWindow::SetRenderViewport(QRenderViewport *viewport)
{
	m_Viewport = viewport;

	m_Context = new QOpenGLContext(this);

	m_Context->setFormat(format());
	m_Context->create();
	m_Context->makeCurrent(this);


	glClearColor(1.0f, 0.0f, 0.4f, 1.0f);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//----------------------------------------------------------
