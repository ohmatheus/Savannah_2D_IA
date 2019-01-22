#include "stdafx.h"
#include "QRenderWindow.h"
#include "QRenderViewport.h"

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
}

//----------------------------------------------------------
