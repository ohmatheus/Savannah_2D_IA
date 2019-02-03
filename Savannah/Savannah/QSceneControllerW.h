#pragma once

#include "IGameController.h"

#include <QWidget>

//----------------------------------------------------------

class QSceneControllerW : public QWidget, public IGameController
{
	using Super = QWidget;
public:
	QSceneControllerW(QWidget *parent);
	virtual ~QSceneControllerW();

	Q_SLOT void			OnSceneStart();
	virtual bool		RequestGameParameters(SGameParameters &to) override;
	void				SetSimulationSpeed(float simuSpeed);

protected:
	QMutex				m_GameLock;
};

//----------------------------------------------------------
