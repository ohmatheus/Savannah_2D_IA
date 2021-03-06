#include "stdafx.h"

#include "QSceneControllerW.h"

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QVBoxLayout>

//----------------------------------------------------------

QSceneControllerW::QSceneControllerW(QWidget *parent)
:	Super(parent)
{
	auto		*dummy = new QWidget(this);

	QVBoxLayout		*rootLayout = new QVBoxLayout(dummy);
	QGridLayout		*layout = new QGridLayout();
	rootLayout->addLayout(layout);
	layout->setSpacing(20);

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
			QIntValidator		*iv = new QIntValidator(this);
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
			QIntValidator		*iv = new QIntValidator(this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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

		{
			m_FleeRadiusA = new QLineEdit(this);
			m_FleeRadiusA->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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

		{
			m_NbrFriendToAttack = new QLineEdit(this);
			m_NbrFriendToAttack->setMaximumWidth(50);
			QIntValidator	*dv = new QIntValidator(this);
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

		{
			m_FriendRadius = new QLineEdit(this);
			m_FriendRadius->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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

		{
			m_LonelinessRadius = new QLineEdit(this);
			m_LonelinessRadius->setMaximumWidth(50);
			QDoubleValidator	*dv = new QDoubleValidator(0.0, 100.0, 2, this);
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

	QGridLayout		*secondLayout = new QGridLayout();
	rootLayout->addLayout(secondLayout);
	secondLayout->setSpacing(5);

	row = 0;
	{
		QLabel	*label = new QLabel("Flag Initial Position", this);
		label->setToolTip("X Y");
		secondLayout->addWidget(label, ++row, 0);

		{
			m_FlagLX = new QLineEdit(this);
			m_FlagLX->setMaximumWidth(35);
			QDoubleValidator	*dv = new QDoubleValidator(this);
			m_FlagLX->setValidator(dv);
			m_FlagLX->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			secondLayout->addWidget(m_FlagLX, row, 1);
			connect(m_FlagLX, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionFlagInitPos.x = m_FlagLX->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_FlagLY = new QLineEdit(this);
			m_FlagLY->setMaximumWidth(35);
			QDoubleValidator	*dv = new QDoubleValidator(this);
			m_FlagLY->setValidator(dv);
			m_FlagLY->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			secondLayout->addWidget(m_FlagLY, row, 2);
			connect(m_FlagLY, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionFlagInitPos.y = m_FlagLY->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_FlagAX = new QLineEdit(this);
			m_FlagAX->setMaximumWidth(35);
			QDoubleValidator	*dv = new QDoubleValidator(this);
			m_FlagAX->setValidator(dv);
			m_FlagAX->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			secondLayout->addWidget(m_FlagAX, row, 3);
			connect(m_FlagAX, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntlepoeFlagInitPos.x = m_FlagAX->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_FlagAY = new QLineEdit(this);
			m_FlagAY->setMaximumWidth(35);
			QDoubleValidator	*dv = new QDoubleValidator(this);
			m_FlagAY->setValidator(dv);
			m_FlagAY->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			secondLayout->addWidget(m_FlagAY, row, 4);
			connect(m_FlagAY, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntlepoeFlagInitPos.y = m_FlagAY->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}
	}

	{
		QLabel	*label = new QLabel("Spawner Initial Position", this);
		label->setToolTip("X Y");
		secondLayout->addWidget(label, ++row, 0);

		{
			m_SpawnLX = new QLineEdit(this);
			m_SpawnLX->setMaximumWidth(35);
			QDoubleValidator	*dv = new QDoubleValidator(this);
			m_SpawnLX->setValidator(dv);
			m_SpawnLX->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			secondLayout->addWidget(m_SpawnLX, row, 1);
			connect(m_SpawnLX, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionSpawnerInitPos.x = m_SpawnLX->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_SpawnLY = new QLineEdit(this);
			m_SpawnLY->setMaximumWidth(35);
			QDoubleValidator	*dv = new QDoubleValidator(this);
			m_SpawnLY->setValidator(dv);
			m_SpawnLY->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			secondLayout->addWidget(m_SpawnLY, row, 2);
			connect(m_SpawnLY, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_LionSpawnerInitPos.y = m_SpawnLY->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_SpawnAX = new QLineEdit(this);
			m_SpawnAX->setMaximumWidth(35);
			QDoubleValidator	*dv = new QDoubleValidator(this);
			m_SpawnAX->setValidator(dv);
			m_SpawnAX->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			secondLayout->addWidget(m_SpawnAX, row, 3);
			connect(m_SpawnAX, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntlepoeSpawnerInitPos.x = m_SpawnAX->text().toFloat();
				m_GameParameters.m_IsDirty = true;
			});
		}

		{
			m_SpawnAY = new QLineEdit(this);
			m_SpawnAY->setMaximumWidth(35);
			QDoubleValidator	*dv = new QDoubleValidator(this);
			m_SpawnAY->setValidator(dv);
			m_SpawnAY->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
			secondLayout->addWidget(m_SpawnAY, row, 4);
			connect(m_SpawnAY, &QLineEdit::editingFinished, [this]()
			{
				SCOPEDLOCK(m_GameLock);
				m_GameParameters.m_AntlepoeSpawnerInitPos.y = m_SpawnAY->text().toFloat();
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

	m_FlagLX->setText(QString::number(m_GameParameters.m_LionFlagInitPos.x));
	m_FlagLY->setText(QString::number(m_GameParameters.m_LionFlagInitPos.y));

	m_FlagAX->setText(QString::number(m_GameParameters.m_AntlepoeFlagInitPos.x));
	m_FlagAY->setText(QString::number(m_GameParameters.m_AntlepoeFlagInitPos.y));

	m_SpawnLX->setText(QString::number(m_GameParameters.m_LionSpawnerInitPos.x));
	m_SpawnLY->setText(QString::number(m_GameParameters.m_LionSpawnerInitPos.y));

	m_SpawnAX->setText(QString::number(m_GameParameters.m_AntlepoeSpawnerInitPos.x));
	m_SpawnAY->setText(QString::number(m_GameParameters.m_AntlepoeSpawnerInitPos.y));
}

//----------------------------------------------------------
