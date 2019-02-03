#pragma once

#include "IGameController.h"

#include <QWidget>

//----------------------------------------------------------

class	QLineEdit;

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
	void				SetGameParameters(const SGameParameters &params);

protected:
	QMutex				m_GameLock;
	QLineEdit			*m_SpawnCountL;
	QLineEdit			*m_SpawnCountA;

	QLineEdit			*m_VelocityL;
	QLineEdit			*m_VelocityA;

	QLineEdit			*m_RotationSpeedL;
	QLineEdit			*m_RotationSpeedA;

	QLineEdit			*m_InitialHealthL;
	QLineEdit			*m_InitialHealthA;

	QLineEdit			*m_DPS_L;
	QLineEdit			*m_DPS_A;

	QLineEdit			*m_AttackRangeL;
	QLineEdit			*m_AttackRangeA;

	// shared
	QLineEdit			*m_FleeRadiusA;
	QLineEdit			*m_NbrFriendToAttack;
	QLineEdit			*m_FriendRadius; // to attack
	QLineEdit			*m_LonelinessRadius;

};

//----------------------------------------------------------
