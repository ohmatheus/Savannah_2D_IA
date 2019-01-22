#include "stdafx.h"

#include "QWorkerObject.h"

//----------------------------------------------------------

QWorkerObject::QWorkerObject(QObject *parent)
	: Super(parent)
{}

//----------------------------------------------------------

QWorkerObject::~QWorkerObject()
{}

//----------------------------------------------------------

void	QWorkerObject::SetFunc(const std::function<void()> &func)
{
	m_Func = func;
}

//----------------------------------------------------------

void	QWorkerObject::Play()
{
	m_Func();
	Q_EMIT End();
}

//----------------------------------------------------------
