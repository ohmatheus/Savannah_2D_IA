#pragma once

#include <QWindow>

#include "IGameWindow.h"

//----------------------------------------------------------

class QRenderViewport;
class QOpenGLContext;
class Game;

//----------------------------------------------------------

class QRenderWindow final : public QWindow, public IGameWindow
{
	Q_OBJECT
public:
	using Super = QWindow;

	QRenderWindow();
	virtual ~QRenderWindow();

	void				SetRenderViewport(QRenderViewport *viewport);

	// Game Thread
	virtual void		SwapBuffers() override;
	virtual void		Initialize() override;
	virtual void		SwapRenderData(SRenderWindowData *&outRenderData) override;
	virtual void		MakeCurrent() override;
	virtual void		SwapEvents(std::vector<QEvent*> *&outEvents) override;

	// UI Thread
	void				SetViewportSize(float x, float y);

	void				SetGame(Game *game) { m_Game = game; }

protected:
	//virtual bool		event(QEvent *ev) override;
	virtual void		keyPressEvent(QKeyEvent *) override;
	virtual void		keyReleaseEvent(QKeyEvent *) override;
	virtual void		mousePressEvent(QMouseEvent *) override;
	virtual void		mouseReleaseEvent(QMouseEvent *) override;
	virtual void		mouseDoubleClickEvent(QMouseEvent *) override;
	virtual void		mouseMoveEvent(QMouseEvent *) override;
	virtual void		wheelEvent(QWheelEvent *) override;

private:
	QRenderViewport		*m_Viewport = nullptr;
	QOpenGLContext		*m_Context = nullptr;
	QSurfaceFormat		*m_SurfaceFormat = nullptr;
	SRenderWindowData	*m_RenderWindowData_UIThread = nullptr;
	Game				*m_Game = nullptr;
	std::vector<QEvent*>*m_EventsToSend;
};

//----------------------------------------------------------
