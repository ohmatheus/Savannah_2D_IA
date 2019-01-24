#pragma once

#include <QWindow>

//----------------------------------------------------------

class QRenderViewport;
class QOpenGLContext;

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

class QRenderWindow final : public QWindow
{
	Q_OBJECT
public:
	using Super = QWindow;

	QRenderWindow();
	virtual ~QRenderWindow();

	void				SetRenderViewport(QRenderViewport *viewport);
	void				SwapBuffers();
	void				Initialize_GameThread();
	void				SwapRenderData();
	void				ProcessRenderData();
		
		// UI Thread
	void				SetViewportSize(float x, float y);


private:
	QRenderViewport		*m_Viewport;
	QOpenGLContext		*m_Context;
	QSurfaceFormat		*m_SurfaceFormat;
	QMutex				m_WindowLock;
	SRenderWindowData	*m_RenderWindowData_UIThread;
	SRenderWindowData	*m_RenderWindowData_GameThread;
	// opengl context

};

//----------------------------------------------------------
