#pragma once

#include <QWidget>

//----------------------------------------------------------

class QSceneControllerW : public QWidget
{
	using Super = QWidget;
public:
	QSceneControllerW(QWidget *parent);
	virtual ~QSceneControllerW();

	Q_SLOT void		OnSceneStart();

protected:
};

//----------------------------------------------------------
