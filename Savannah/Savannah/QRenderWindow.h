#pragma once

#include <QWindow>

//----------------------------------------------------------

class QRenderViewport;
class QOpenGLContext;

//----------------------------------------------------------

class QRenderWindow final : public QWindow
{
	Q_OBJECT
public:
	using Super = QWindow;

	QRenderWindow();
	virtual ~QRenderWindow();

	void				SetRenderViewport(QRenderViewport *viewport);


private:
	QRenderViewport		*m_Viewport;
	QOpenGLContext		*m_Context;
	QSurfaceFormat		*m_SurfaceFormat;
	// opengl context
};

//----------------------------------------------------------
