#include "stdafx.h"
#include "QRenderViewport.h"
#include "QRenderWindow.h"

//----------------------------------------------------------

QRenderViewport::QRenderViewport(QWidget *parent)
:	Super(parent)
{

}

//----------------------------------------------------------

QRenderViewport::~QRenderViewport()
{

}

//----------------------------------------------------------

void	QRenderViewport::Setup(QWidget *internalContainer, QRenderWindow *internalWindow)
{
	m_InternalContainer = internalContainer;
	m_InternalWindow = internalWindow;

	QVBoxLayout	*layout = new QVBoxLayout();

	setLayout(layout);
	layout->setSpacing(0);
	layout->setContentsMargins(0, 0, 0, 0);
	m_InternalWindow->SetRenderViewport(this);

	{
		QToolBar	*toolbar = new QToolBar(this);
		layout->addWidget(toolbar, 0);
		//m_TopToolbar = toolbar;
	}

	assert(m_InternalContainer != nullptr);

	layout->addWidget(m_InternalContainer, 1);

	// Viewport/camera controls
}

//----------------------------------------------------------

