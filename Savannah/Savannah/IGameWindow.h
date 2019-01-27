#pragma once

#include <QEvent> // god..
#include <vector>

//----------------------------------------------------------

struct SRenderWindowData
{
public:
	void	Clear()
	{
		m_Dirty = false;
		m_X = 0.f;
		m_Y = 0.f;
	}

	bool	m_Dirty = false;
	float	m_X = 0.f;
	float	m_Y = 0.f;
};

//----------------------------------------------------------

class IGameWindow
{
public:
	IGameWindow();
	virtual ~IGameWindow();

	virtual void		SwapBuffers() = 0;
	virtual void		Initialize() = 0;
	virtual void		SwapRenderData(SRenderWindowData *&outRenderData) = 0;
	virtual void		MakeCurrent() = 0;
	virtual void		SwapEvents(std::vector<QEvent> *&outEvents) = 0;

protected:
	QMutex				m_WindowLock; // temp from Qt
	QMutex				m_EventLock; // temp from Qt

};

//----------------------------------------------------------
