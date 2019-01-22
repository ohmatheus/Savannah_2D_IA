#pragma once

#include <QWindow>

//----------------------------------------------------------

class QRenderViewport;

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

	// opengl context
};

//----------------------------------------------------------
