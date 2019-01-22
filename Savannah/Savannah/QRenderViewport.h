#pragma once

#include <QFrame>

//----------------------------------------------------------

class	QRenderWindow;

//----------------------------------------------------------

class QRenderViewport final : public QFrame
{
	Q_OBJECT
public:
	using Super = QFrame;

	QRenderViewport(QWidget *parent);
	virtual		~QRenderViewport();

	void				Setup(QWidget *internalContainer, QRenderWindow *internalWindow);

private:
	QRenderWindow		*m_InternalWindow;
	QWidget				*m_InternalContainer;
};

//----------------------------------------------------------