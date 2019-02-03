#include "stdafx.h"

#include "QSceneControllerW.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>

#include <QPushButton>
//----------------------------------------------------------

QSceneControllerW::QSceneControllerW(QWidget *parent)
:	Super(parent)
{
	auto		*dummy = new QWidget(this);

	auto		*layout = new QGridLayout(dummy);
	layout->setSpacing(20);
	//layout->setContentsMargins(0, 0, 0, 0);
	//layout->setColumnMinimumWidth(0, 50);
	//layout->setColumnMinimumWidth(1, 50);
	//layout->setColumnMinimumWidth(2, 50);

	//setEnabled(false);

	int row = 0;
	{
		QLabel		*label = new QLabel("Lions", this);
		layout->addWidget(label, row, 1);
	}

	{
		QLabel		*label = new QLabel("Antelope", this);
		layout->addWidget(label, row, 2);
	}

	{
		QLabel		*label = new QLabel("Spawn Count", this);
		layout->addWidget(label, ++row, 0);

		{
			m_SpawnCountL = new QLineEdit(this);
			m_SpawnCountL->setMaximumWidth(50);
			//QDoubleValidator *dv = new QDoubleValidator(0.0, 5.0, 2); // [0, 5] with 2 decimals of precision
			QIntValidator		*iv = new QIntValidator();
			m_SpawnCountL->setValidator(iv);
			m_SpawnCountL->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_SpawnCountL, row, 1);
			connect(m_SpawnCountL, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionSpawnCount = m_SpawnCountL->text().toInt();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_SpawnCountA = new QLineEdit(this);
			m_SpawnCountA->setMaximumWidth(50);
			QIntValidator		*iv = new QIntValidator();
			m_SpawnCountA->setValidator(iv);
			m_SpawnCountA->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_SpawnCountA, row, 2);
			connect(m_SpawnCountA, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeSpawnCount = m_SpawnCountA->text().toInt();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Velocity", this);
		layout->addWidget(label, ++row, 0);

		{
			m_VelocityL = new QLineEdit(this);
			m_VelocityL->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_VelocityL->setValidator(dv);
			m_VelocityL->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_VelocityL, row, 1);
			connect(m_VelocityL, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionVelocity = m_VelocityL->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_VelocityA = new QLineEdit(this);
			m_VelocityA->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_VelocityA->setValidator(dv);
			m_VelocityA->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_VelocityA, row, 2);
			connect(m_VelocityA, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeVelocity = m_VelocityA->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Rotation Speed", this);
		layout->addWidget(label, ++row, 0);

		{
			m_RotationSpeedL = new QLineEdit(this);
			m_RotationSpeedL->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_RotationSpeedL->setValidator(dv);
			m_RotationSpeedL->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_RotationSpeedL, row, 1);
			connect(m_RotationSpeedL, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionRotationSpeed = m_RotationSpeedL->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_RotationSpeedA = new QLineEdit(this);
			m_RotationSpeedA->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_RotationSpeedA->setValidator(dv);
			m_RotationSpeedA->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_RotationSpeedA, row, 2);
			connect(m_RotationSpeedA, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeRotationSpeed = m_RotationSpeedA->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Initial Health", this);
		layout->addWidget(label, ++row, 0);

		{
			m_InitialHealthL = new QLineEdit(this);
			m_InitialHealthL->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_InitialHealthL->setValidator(dv);
			m_InitialHealthL->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_InitialHealthL, row, 1);
			connect(m_InitialHealthL, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionInitialHealth = m_InitialHealthL->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_InitialHealthA = new QLineEdit(this);
			m_InitialHealthA->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_InitialHealthA->setValidator(dv);
			m_InitialHealthA->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_InitialHealthA, row, 2);
			connect(m_InitialHealthA, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeInitialHealth = m_InitialHealthA->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Dps", this);
		label->setToolTip("Damage/seconds.");
		layout->addWidget(label, ++row, 0);

		{
			m_DPS_L = new QLineEdit(this);
			m_DPS_L->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_DPS_L->setValidator(dv);
			m_DPS_L->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_DPS_L, row, 1);
			connect(m_DPS_L, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionDPS = m_DPS_L->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_DPS_A = new QLineEdit(this);
			m_DPS_A->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_DPS_A->setValidator(dv);
			m_DPS_A->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_DPS_A, row, 2);
			connect(m_DPS_A, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeDPS = m_DPS_A->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Attack Range", this);
		label->setToolTip("Attack range.");
		layout->addWidget(label, ++row, 0);

		{
			m_AttackRangeL = new QLineEdit(this);
			m_AttackRangeL->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_AttackRangeL->setValidator(dv);
			m_AttackRangeL->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_AttackRangeL, row, 1);
			connect(m_AttackRangeL, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionAttackRadius = m_AttackRangeL->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_AttackRangeA = new QLineEdit(this);
			m_AttackRangeA->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_AttackRangeA->setValidator(dv);
			m_AttackRangeA->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_AttackRangeA, row, 2);
			connect(m_AttackRangeA, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeAttackRadius = m_AttackRangeA->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Security Radius", this);
		label->setToolTip("Radius to ask self he has to engage or flee.");
		layout->addWidget(label, ++row, 0);

		/*{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}*/

		{
			m_FleeRadiusA = new QLineEdit(this);
			m_FleeRadiusA->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_FleeRadiusA->setValidator(dv);
			m_FleeRadiusA->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_FleeRadiusA, row, 2);
			connect(m_FleeRadiusA, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeFleeRadius = m_FleeRadiusA->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Near Friend to Attack", this);
		label->setToolTip("Number of friends within 'Near Friend Radius To Attack' to know if self can engage enemy.");
		layout->addWidget(label, ++row, 0);

		/*{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}*/

		{
			m_NbrFriendToAttack = new QLineEdit(this);
			m_NbrFriendToAttack->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_NbrFriendToAttack->setValidator(dv);
			m_NbrFriendToAttack->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_NbrFriendToAttack, row, 2);
			connect(m_NbrFriendToAttack, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeFriendCountToAttack = m_NbrFriendToAttack->text().toInt();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Near Friend Radius To Attack", this);
		label->setToolTip("Radius to consider potential friends to attack.");
		layout->addWidget(label, ++row, 0);
		/*{
			QLineEdit			*line = new QLineEdit(this);
			line->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
			line->setValidator(dv);
			line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(line, row, 1);
		}*/

		{
			m_FriendRadius = new QLineEdit(this);
			m_FriendRadius->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_FriendRadius->setValidator(dv);
			m_FriendRadius->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_FriendRadius, row, 2);
			connect(m_FriendRadius, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeFriendCountRadius = m_FriendRadius->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Loneliness Radius", this);
		label->setToolTip("Maximal distance between siblings before they feel alone.");
		layout->addWidget(label, ++row, 0);
		/*{
		QLineEdit			*line = new QLineEdit(this);
		line->setMaximumWidth(50);
		QDoubleValidator	*dv = new QDoubleValidator(0.0, 5.0, 2);
		line->setValidator(dv);
		line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
		layout->addWidget(line, row, 1);
		}*/

		{
			m_LonelinessRadius = new QLineEdit(this);
			m_LonelinessRadius->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2);
			m_LonelinessRadius->setValidator(dv);
			m_LonelinessRadius->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			layout->addWidget(m_LonelinessRadius, row, 2);
			connect(m_LonelinessRadius, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntelopeLonelinessRadius = m_LonelinessRadius->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}
}

//----------------------------------------------------------

QSceneControllerW::~QSceneControllerW()
{}

//----------------------------------------------------------

bool	QSceneControllerW::RequestGameParameters(SGameParameters &to)
{
	if (m_GameParameters.m_IsDirty) // ReadOnly
	{
		SCOPEDLOCK(m_GameLock);
		to.m_IsDirty = m_GameParameters.m_IsDirty;
		to.m_SimulationSpeed = m_GameParameters.m_SimulationSpeed;
		to = m_GameParameters;
		m_GameParameters.m_IsDirty = false;
		return true;
	}
	return false;
}

//----------------------------------------------------------

void	QSceneControllerW::SetSimulationSpeed(float simuSpeed)
{
	SCOPEDLOCK(m_GameLock);
	m_GameParameters.m_SimulationSpeed = simuSpeed;
	m_GameParameters.m_IsDirty = true;
}

//----------------------------------------------------------

void	QSceneControllerW::SetGameParameters(const SGameParameters &params)
{
	m_GameParameters = params;

	// witch reflexion: automate this, didn't had time

	m_SpawnCountL->setText(QString::number(m_GameParameters.m_LionSpawnCount));
	m_SpawnCountA->setText(QString::number(m_GameParameters.m_AntelopeSpawnCount));

	m_VelocityL->setText(QString::number(m_GameParameters.m_LionVelocity));
	m_VelocityA->setText(QString::number(m_GameParameters.m_AntelopeVelocity));

	m_RotationSpeedL->setText(QString::number(m_GameParameters.m_LionRotationSpeed));
	m_RotationSpeedA->setText(QString::number(m_GameParameters.m_AntelopeRotationSpeed));

	m_InitialHealthL->setText(QString::number(m_GameParameters.m_LionInitialHealth));
	m_InitialHealthA->setText(QString::number(m_GameParameters.m_AntelopeInitialHealth));

	m_DPS_L->setText(QString::number(m_GameParameters.m_LionDPS));
	m_DPS_A->setText(QString::number(m_GameParameters.m_AntelopeDPS));

	m_AttackRangeL->setText(QString::number(m_GameParameters.m_LionAttackRadius));
	m_AttackRangeA->setText(QString::number(m_GameParameters.m_AntelopeAttackRadius));

	m_FleeRadiusA->setText(QString::number(m_GameParameters.m_AntelopeFleeRadius));
	m_NbrFriendToAttack->setText(QString::number(m_GameParameters.m_AntelopeFriendCountToAttack));
	m_FriendRadius->setText(QString::number(m_GameParameters.m_AntelopeFriendCountRadius));
	m_LonelinessRadius->setText(QString::number(m_GameParameters.m_AntelopeLonelinessRadius));
}

//----------------------------------------------------------
